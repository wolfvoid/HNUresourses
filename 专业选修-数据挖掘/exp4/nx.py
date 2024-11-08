import numpy as np
import networkx as nx
import dgl
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader

# 读取基因列表
gene_list_file = "GeneList.txt"
gene_list = [line.strip() for line in open(gene_list_file)]

# 读取基因关系和置信分数
link_file = "Positive_LinkSL.txt"
edges = []
edge_confidences = []
with open(link_file, 'r') as f:
    for line in f:
        gene1, gene2, confidence = line.strip().split()
        edges.append((gene_list.index(gene1), gene_list.index(gene2)))
        edge_confidences.append(float(confidence))

# 读取基因特征
feature1_file = "feature1_go.txt"
feature2_file = "feature2_ppi.txt"
feature1 = np.loadtxt(feature1_file)
feature2 = np.loadtxt(feature2_file)

# 构建图
G = nx.Graph()
G.add_nodes_from(range(len(gene_list)))
G.add_edges_from(edges)

# 转换成DGL图，并添加自环
g = dgl.from_networkx(G)
g = dgl.add_self_loop(g)

# 将基因特征转换为PyTorch张量
feature1 = torch.FloatTensor(feature1)
feature2 = torch.FloatTensor(feature2)

# 定义GCN模型
class GCN(nn.Module):
    def __init__(self, in_feats, out_feats):
        super(GCN, self).__init__()
        self.conv1 = dgl.nn.GraphConv(in_feats, out_feats)
        self.conv2 = dgl.nn.GraphConv(out_feats, out_feats)  # 输出维度与第一层相同

    def forward(self, g, features):
        g = dgl.add_self_loop(g)  # 在图卷积之前添加自环
        x = self.conv1(g, features)
        x = torch.relu(x)
        x = self.conv2(g, x)
        return x

# 训练GCN模型
in_feats = 256  # 输入特征的维度
out_feats = 256  # 输出特征的维度（与第一层GCN层的输出特征维度相同）
model = GCN(in_feats, out_feats)
optimizer = optim.Adam(model.parameters(), lr=0.01)
criterion = nn.MSELoss()

# 将特征传递给模型
features = torch.cat([feature1, feature2], dim=1)
output = model(g, features)

# 准备标签
labels = torch.FloatTensor(edge_confidences)

# 训练模型
num_epochs = 100
for epoch in range(num_epochs):
    optimizer.zero_grad()
    output = model(g, features)
    loss = criterion(output.view(-1), labels)  # 使用 view 调整输出维度
    loss.backward()
    optimizer.step()
    print(f'Epoch {epoch + 1}/{num_epochs}, Loss: {loss.item()}')

# 预测链接关系
with torch.no_grad():
    predictions = model(g, features).unsqueeze(1)  # 使用 unsqueeze 添加额外的维度

# 选择置信分数较高的链接关系
threshold = 0.5
significant_links = [(gene_list[u], gene_list[v], confidence)
                     for (u, v), confidence in zip(edges, predictions) if confidence > threshold]

# 打印显著链接关系
print("Significant Links:")
for link in significant_links:
    print(link)
