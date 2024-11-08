import dgl
import torch
import numpy as np

# 读取基因列表
with open('GeneList.txt', 'r') as f:
    gene_list = [line.strip() for line in f]
# 构建基因到索引的映射
gene_dict = {gene: idx for idx, gene in enumerate(gene_list)}

# 读取基因关系和置信分数
with open('Positive_LinkSL.txt', 'r') as f:
    edges = [line.strip().split() for line in f]
# 提取基因关系的源节点、目标节点和置信分数
src_nodes = [gene_dict[edge[0]] for edge in edges] + [gene_dict[edge[1]] for edge in edges]
dst_nodes = [gene_dict[edge[1]] for edge in edges] + [gene_dict[edge[0]] for edge in edges]
confidence_scores = [float(edge[2]) for edge in edges] + [float(edge[2]) for edge in edges]

# 读取特征
with open('feature1_go.txt', 'r') as file:
    feature1_go = np.array([list(map(float, line.split())) for line in file])
with open('feature2_ppi.txt', 'r') as file:
    feature2_ppi = np.array([list(map(float, line.split())) for line in file])

# 构建图
edges = torch.tensor(src_nodes),torch.tensor(dst_nodes)
graph = dgl.graph(edges)
graph.edata['confidence'] = torch.tensor(confidence_scores,dtype=torch.float32)
graph.ndata['feature1_go'] = torch.tensor(feature1_go,dtype=torch.float32)
graph.ndata['feature2_ppi'] = torch.tensor(feature2_ppi,dtype=torch.float32)

"""print(graph)
# 输出边的权值值
edge_weights = graph.edata['confidence'].squeeze().numpy()
print("Edge Weights:")
print(edge_weights)
# 输出节点特征 'feature1_go'
feature1_go_values = graph.ndata['feature1_go'].squeeze().numpy()
print("Node Feature 'feature1_go':")
print(feature1_go_values)
# 输出节点特征 'feature2_ppi'
feature2_ppi_values = graph.ndata['feature2_ppi'].squeeze().numpy()
print("Node Feature 'feature2_ppi':")
print(feature2_ppi_values)"""

print(graph)


# 构建一个2层的GNN模型
import dgl.nn as dglnn
import torch.nn as nn
import torch.nn.functional as F
class SAGE(nn.Module):
    def __init__(self, in_feats, hid_feats, out_feats):
        super().__init__()
        # 实例化SAGEConve，in_feats是输入特征的维度，out_feats是输出特征的维度，aggregator_type是聚合函数的类型
        self.conv1 = dglnn.SAGEConv(
            in_feats=in_feats, out_feats=hid_feats, aggregator_type='mean')
        self.conv2 = dglnn.SAGEConv(
            in_feats=hid_feats, out_feats=out_feats, aggregator_type='mean')

    def forward(self, graph, inputs):
        # 输入是节点的特征
        h = self.conv1(graph, inputs)
        h = F.relu(h)
        h = self.conv2(graph, h)
        return h

def construct_negative_graph(graph, k):
    src, dst = graph.edges()

    neg_src = src.repeat_interleave(k)
    neg_dst = torch.randint(0, graph.num_nodes(), (len(src) * k,))
    return dgl.graph((neg_src, neg_dst), num_nodes=graph.num_nodes())

import dgl.function as fn
class DotProductPredictor(nn.Module):
    def forward(self, graph, h):
        # h是从5.1节的GNN模型中计算出的节点表示
        with graph.local_scope():
            graph.ndata['h'] = h
            graph.apply_edges(fn.u_dot_v('h', 'h', 'score'))
            return graph.edata['score']

def compute_loss(pos_score, neg_score):
    # 间隔损失
    n_edges = pos_score.shape[0]
    return (1 - pos_score.unsqueeze(1) + neg_score.view(n_edges, -1)).clamp(min=0).mean()

class Model(nn.Module):
    def __init__(self, in_features, hidden_features, out_features):
        super().__init__()
        self.sage = SAGE(in_features, hidden_features, out_features)
        self.pred = DotProductPredictor()
    def forward(self, g, neg_g, x):
        h = self.sage(g, x)
        #return self.pred(g, h), self.pred(neg_g, h)
        pos_score = self.pred(g, h)
        neg_score = self.pred(neg_g, h)
        return pos_score, neg_score

node_features = graph.ndata['feature1_go']
n_features = node_features.shape[1]
k = 1
model = Model(n_features, 10, 5)
opt = torch.optim.Adam(model.parameters())
for epoch in range(1):
    negative_graph = construct_negative_graph(graph, k)
    pos_score, neg_score = model(graph, negative_graph, node_features)
    loss = compute_loss(pos_score, neg_score)
    opt.zero_grad()
    loss.backward()
    opt.step()
    print(f'Epoch {epoch + 1}, Loss: {loss.item()}')









"""# 输出边的置信度分布
print("Edge Confidence Distribution:")
print(pos_score.detach().numpy())


import networkx as nx
import matplotlib.pyplot as plt
from sklearn.manifold import TSNE

true_labels = torch.randint(0, 3, (len(gene_list),))  # 0, 1, 2 之间的随机标签

# 获取节点表示
with torch.no_grad():
    node_embeddings = model.sage(graph, node_features).numpy()

# 将节点表示降维到二维空间进行可视化
tsne = TSNE(n_components=2, random_state=42)
node_embeddings_2d = tsne.fit_transform(node_embeddings)

# 构建 NetworkX 图
G = nx.Graph()
for i, gene in enumerate(gene_list):
    G.add_node(gene, label=true_labels[i].item(), color=true_labels[i].item())

for edge, score in zip(edges, pos_score.detach().numpy()):
    G.add_edge(gene_list[edge[0]], gene_list[edge[1]], score=score)

# 绘制图
plt.figure(figsize=(12, 8))
pos = nx.spring_layout(G, seed=42)
node_color = [true_labels[i].item() for i in range(len(gene_list))]

# 绘制节点
nx.draw_networkx_nodes(G, pos, node_size=100, node_color=node_color, cmap='viridis')

# 绘制链接预测的边
edge_color = ['b' if score > 0.5 else 'r' for score in nx.get_edge_attributes(G, 'score').values()]
nx.draw_networkx_edges(G, pos, edge_color=edge_color, width=1.5, alpha=0.6)

# 绘制节点标签
labels = nx.get_node_attributes(G, 'label')
nx.draw_networkx_labels(G, pos, labels=labels, font_size=8)

plt.title('Link Prediction Visualization')
plt.show()"""








"""from sklearn.metrics import precision_recall_curve
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, roc_auc_score, roc_curve, average_precision_score

# 将预测的置信度转换为二分类标签
threshold = 0.5  # 可以根据具体情况调整阈值
predicted_labels = np.where(pos_score.detach().numpy() > threshold, 1, 0)

# 计算 Accuracy、Precision、Recall、F1 Score
accuracy = accuracy_score(true_labels.numpy(), predicted_labels)
precision = precision_score(true_labels.numpy(), predicted_labels)
recall = recall_score(true_labels.numpy(), predicted_labels)
f1 = f1_score(true_labels.numpy(), predicted_labels)

print(f"Accuracy: {accuracy:.4f}")
print(f"Precision: {precision:.4f}")
print(f"Recall: {recall:.4f}")
print(f"F1 Score: {f1:.4f}")

# 计算 ROC 和 AUC
fpr, tpr, _ = roc_curve(true_labels.numpy(), pos_score.detach().numpy())
roc_auc = roc_auc_score(true_labels.numpy(), pos_score.detach().numpy())

# 绘制 ROC 曲线
plt.figure(figsize=(8, 6))
plt.plot(fpr, tpr, color='darkorange', lw=2, label=f'ROC curve (AUC = {roc_auc:.2f})')
plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--')
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('Receiver Operating Characteristic (ROC) Curve')
plt.legend(loc="lower right")
plt.show()

# 计算 AUPR
precision, recall, _ = precision_recall_curve(true_labels.numpy(), pos_score.detach().numpy())
aupr = average_precision_score(true_labels.numpy(), pos_score.detach().numpy())

# 绘制 Precision-Recall 曲线
plt.figure(figsize=(8, 6))
plt.step(recall, precision, color='b', alpha=0.2, where='post')
plt.fill_between(recall, precision, step='post', alpha=0.2, color='b')
plt.xlabel('Recall')
plt.ylabel('Precision')
plt.title('Precision-Recall Curve (AUPR = {0:.2f})'.format(aupr))
plt.show()"""
