import networkx as nx
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import matplotlib.pyplot as plt
from torch_geometric.data import Data, DataLoader
from torch_geometric.nn import GATConv

# 构建基因关系图
# 提取基因关系，根据数据集的说明文件，第一列和第二列分别代表关联的两个基因，第三列代表的是关系的置信分数
# 这里使用networkx创建一个有向图或无向图，其中基因是图的节点，关系是图的边，将关系的置信分数作为边的权重

# 读取关系数据
edges = []
with open('Positive_LinkSL.txt', 'r') as f:
    for line in f:
        gene1, gene2, confidence = line.strip().split('\t')
        edges.append((gene1, gene2,float(confidence)))

# 创建图并添加边
gene_graph = nx.Graph()
gene_graph.add_weighted_edges_from(edges)

# 添加节点的特征
# 每一个基因对应128维属性，可以把这些特征添加到图的节点上

# 读取基因名
genes = []
with open('GeneList.txt', 'r') as f_genes:
    for line in f_genes:
        genes.append(line.strip())

len(genes)


# 从'feature_ppi_128.txt'中读取特征数据并添加到图中
features_ppi = {}
with open('feature2_ppi.txt', 'r') as f_ppi:
    for i, line in enumerate(f_ppi):
        gene = genes[i]
        feature_values = list(map(float,line.strip().split(' ')))
        features_ppi[gene] = np.array(feature_values)
        if gene_graph.has_node(gene):
            # 节点存在于图中
            gene_graph.nodes[gene]['feature_ppi'] = np.array(feature_values)
        else:
            # 节点不存在于图中，输出信息
            print(f"Gene {gene} not found in the graph.")




# 从'feature_go_128.txt'中读取特征数据并添加到图中
features_go = {}
with open('feature1_go.txt', 'r') as f_go:
    for i, line in enumerate(f_go):
        gene = genes[i]
        feature_values = list(map(float, line.strip().split(' ')))
        features_go[gene] = np.array(feature_values)
        if gene_graph.has_node(gene):
            # 节点存在于图中
            gene_graph.nodes[gene]['feature_go'] = np.array(feature_values)
        else:
            # 节点不存在于图中，输出信息
            print(f"Gene {gene} not found in the graph.")


# 模型构建
# 将图转换为pytorch geometric data 对象
# 将基因名称映射到索引
gene_to_index = {gene: i for i, gene in enumerate(genes)}
# 将边的基因名称转换为索引
edges_index = torch.tensor([(gene_to_index[gene1], gene_to_index[gene2]) for gene1, gene2, _ in edges], dtype=torch.long).t().contiguous()
x_ppi = torch.tensor([gene_graph.nodes[node]['feature_ppi'] for node in gene_graph.nodes], dtype=torch.float32)
x_go = torch.tensor([gene_graph.nodes[node]['feature_go'] for node in gene_graph.nodes], dtype=torch.float32)
y = torch.tensor([0]*len(gene_graph.nodes)) # 根据任务设定标签
data = Data(x_ppi=x_ppi, x_go=x_go, edge_index=edges_index, y=y)
# edges_index.shape
# x_ppi.shape
# x_go.shape
# y.shape





# 可视化关系图的结构
edge_index_np = data.edge_index.numpy()
G = nx.Graph()
G.add_edges_from(edge_index_np.T)
# pos = nx.spring_layout(G)
# degrees = dict(G.degree())
# node_sizes = [deg * 10 for deg in degrees.values()]
plt.figure(figsize=(8, 6))  # 添加此行以创建新的图形对象
nx.draw(G, with_labels=True, node_size=30, alpha=1.0, width=0.1, font_size=4, pos=nx.spring_layout(G))
plt.title('Graph Structure')
plt.show()







# 定义图注意力网络模型
class GAT(nn.Module):
    def __init__(self, in_channels, hidden_channels, out_channels, heads):
        super(GAT, self).__init__()
        self.conv1 = GATConv(in_channels, hidden_channels, heads=heads)
        self.conv2 = GATConv(hidden_channels * heads*2, out_channels, heads=1)

    def forward(self, data):
        x_ppi, x_go, edge_index = data.x_ppi, data.x_go, data.edge_index

        x_ppi = self.conv1(x_ppi, edge_index)
        x_go = self.conv1(x_go, edge_index)

        x = torch.cat([x_ppi, x_go], dim=-1)
        x = torch.relu(x)

        x = self.conv2(x, edge_index)
        return x





# 创建模型
model = GAT(in_channels=128, hidden_channels=64, out_channels=32, heads=4)

# 定义损失函数和优化器
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=0.0005)

# 训练模型
num_epochs = 100
losses = []
for epoch in range(num_epochs):
    out = model(data)
    loss = criterion(out, data.y)
    optimizer.zero_grad()
    loss.backward()
    losses.append(loss)
    optimizer.step()

    # 打印训练过程中的损失
    print(f'Epoch {epoch + 1}/{num_epochs}, Loss: {loss.item()}')






# 可视化训练过程中的损失
plt.figure(figsize=(8, 5))
plt.plot(range(1, num_epochs+1), [l.detach().item() for l in losses], marker='o')
plt.title('Training Loss over Epochs')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.grid(True)
plt.show()




# 提取节点表示
with torch.no_grad():
    model.eval()
    node_representations = model(data).detach().numpy()

# 可视化节点表示的分布
plt.scatter(node_representations[:, 0], node_representations[:, 1], c=data.y.numpy(), cmap='viridis')
plt.title('Node Representations')
plt.colorbar()
plt.show()







