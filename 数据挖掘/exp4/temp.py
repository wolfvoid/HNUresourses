import dgl
import torch
import torch.nn as nn
import torch.nn.functional as F
from dgl.nn.pytorch import SAGEConv

# Define DotPredictor
class DotPredictor(nn.Module):
    def forward(self, g, h):
        with g.local_scope():
            g.ndata['h'] = h
            g.apply_edges(lambda edges: {'score': torch.sum(edges.src['h'] * edges.dst['h'], dim=1)})
            return g.edata['score']

# Define GraphSAGE
class GraphSAGE(nn.Module):
    def __init__(self, in_feats, h_feats):
        super(GraphSAGE, self).__init__()
        self.conv1 = SAGEConv(in_feats, h_feats, 'mean')
        self.conv2 = SAGEConv(h_feats, h_feats, 'mean')

    def forward(self, g, features):
        h = self.conv1(g, features)
        h = F.relu(h)
        h = self.conv2(g, h)
        return h

# Define Link Prediction Model
class LinkPredictionModel(nn.Module):
    def __init__(self, in_feats, h_feats):
        super(LinkPredictionModel, self).__init__()
        self.gnn = GraphSAGE(in_feats, h_feats)
        self.predictor = DotPredictor()

    def forward(self, g, features):
        h = self.gnn(g, features)
        return self.predictor(g, h)

# 读取基因列表
with open('GeneList.txt', 'r') as f:
    gene_list = [line.strip() for line in f]

# 构建基因到索引的映射
gene_dict = {gene: idx for idx, gene in enumerate(gene_list)}

# 读取基因关系和置信分数
with open('Positive_LinkSL.txt', 'r') as f:
    edges = [line.strip().split() for line in f]

# 提取基因关系的源节点、目标节点和置信分数
src_nodes = [gene_dict[edge[0]] for edge in edges]
dst_nodes = [gene_dict[edge[1]] for edge in edges]
confidence_scores = [float(edge[2]) for edge in edges]

# 创建有向图
graph_directed = dgl.graph((src_nodes, dst_nodes))
graph_directed.edata['confidence'] = torch.tensor(confidence_scores).view(-1, 1)

# 交换源节点和目标节点的位置，创建反向边
graph_reverse = dgl.graph((dst_nodes, src_nodes))
graph_reverse.edata['confidence'] = torch.tensor(confidence_scores).view(-1, 1)

# 将两个有向图的边连接起来，得到包含两次边的无向图
graph_undirected = dgl.graph((graph_directed.edges()[0].tolist() + graph_reverse.edges()[0].tolist(),
                              graph_directed.edges()[1].tolist() + graph_reverse.edges()[1].tolist()))
graph_undirected.edata['confidence'] = torch.cat([graph_directed.edata['confidence'], graph_reverse.edata['confidence']])

# Define the model
model = LinkPredictionModel(in_feats=1, h_feats=16)

# Training loop
optimizer = torch.optim.Adam(model.parameters(), lr=0.01)

for epoch in range(50):
    # Forward pass
    logits = model(graph_undirected, torch.ones(len(gene_list), 1))

    # Binary cross entropy loss
    pos_loss = F.binary_cross_entropy_with_logits(logits, torch.ones(graph_undirected.num_edges()))
    neg_loss = F.binary_cross_entropy_with_logits(logits, torch.zeros(graph_undirected.num_edges()))
    loss = pos_loss + neg_loss

    # Backward pass
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    print(f'Epoch {epoch + 1}/50, Loss: {loss.item()}')

# Evaluate the model
model.eval()
with torch.no_grad():
    model.eval()
    new_edges = torch.tensor([[0, 1], [500, 6888], [50, 6588]])  # 替换为你自己的新边
    pred_scores = torch.sigmoid(model(graph_undirected, torch.ones(len(gene_list), 1)))
    pred_scores = pred_scores[new_edges[:, 0]] * pred_scores[new_edges[:, 1]]
    print(f'Predicted Scores for New Edges: {pred_scores}')

