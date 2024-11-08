import torch
import torch.nn as nn
import torch.optim as optim
from torch_geometric.data import Data
from torch_geometric.nn import GATConv
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, roc_auc_score, average_precision_score, roc_curve, auc
from sklearn.model_selection import train_test_split
import numpy as np
import matplotlib.pyplot as plt

# 读取数据
def read_data(file_path):
    with open(file_path, 'r') as f:
        data = f.read().splitlines()
    return data

# 构建图数据
def build_graph_data(gene_list, link_list, feature1, feature2):
    edge_index = []
    edge_attr = []
    x1 = []
    x2 = []

    gene_dict = {gene: idx for idx, gene in enumerate(gene_list)}

    for link in link_list:
        gene1, gene2, confidence = link.split('\t')
        if gene1 in gene_dict and gene2 in gene_dict:
            edge_index.append([gene_dict[gene1], gene_dict[gene2]])
            edge_attr.append(float(confidence))

    edge_index = torch.tensor(edge_index, dtype=torch.long).t().contiguous()
    edge_attr = torch.tensor(edge_attr, dtype=torch.float).view(-1, 1)

    for gene in gene_list:
        if gene in gene_dict:
            x1.append(feature1[gene_dict[gene]])
            x2.append(feature2[gene_dict[gene]])

    x1 = torch.tensor(x1, dtype=torch.float)
    x2 = torch.tensor(x2, dtype=torch.float)

    data = Data(x1=x1, x2=x2, edge_index=edge_index, edge_attr=edge_attr)
    return data

# GAT 模型定义
class GATModel(nn.Module):
    def __init__(self, in_channels, out_channels, heads):
        super(GATModel, self).__init__()
        self.conv1 = GATConv(in_channels, out_channels, heads=heads)

    def forward(self, x, edge_index, edge_attr):
        x = self.conv1(x, edge_index, edge_attr)
        return x

# 训练模型
def train(model, data, optimizer, criterion, epochs):
    model.train()
    losses = []  # 用于记录每个 epoch 的损失值
    for epoch in range(epochs):
        optimizer.zero_grad()
        out = model(data.x1, data.edge_index, data.edge_attr)
        loss = criterion(out, data.x2)
        loss.backward()
        optimizer.step()
        losses.append(loss.item())  # 记录当前 epoch 的损失值
        print(f'Epoch {epoch + 1}/{epochs}, Loss: {loss.item()}')

    # 绘制损失曲线图
    plt.plot(losses)
    plt.title('Training Loss Over Epochs')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.show()


# 评估链接预测结果
def evaluate(y_true, y_pred):
    y_true = (y_true > 0.5).int().cpu().numpy()
    y_pred = (y_pred > 0.5).int().cpu().numpy()

    accuracy = accuracy_score(y_true, y_pred)
    precision = precision_score(y_true, y_pred, average='micro')
    recall = recall_score(y_true, y_pred, average='micro')
    f1 = f1_score(y_true, y_pred, average='micro')
    roc_auc = roc_auc_score(y_true, y_pred)
    aupr = average_precision_score(y_true, y_pred)

    return accuracy, precision, recall, f1, roc_auc, aupr

# 读取数据
gene_list = read_data('GeneList.txt')
link_list = read_data('Positive_LinkSL.txt')
feature1 = np.loadtxt('feature1_go.txt')
feature2 = np.loadtxt('feature2_ppi.txt')

# 划分数据集和测试集
train_gene_list, test_gene_list = train_test_split(gene_list, test_size=0.2, random_state=42)

# 构建训练集和测试集的图数据
train_data = build_graph_data(train_gene_list, link_list, feature1, feature2)
test_data = build_graph_data(test_gene_list, link_list, feature1, feature2)

# 创建并训练 GAT 模型
model = GATModel(in_channels=128, out_channels=128, heads=1)
optimizer = optim.Adam(model.parameters(), lr=0.001)
criterion = nn.MSELoss()

train(model, train_data, optimizer, criterion, epochs=200)

# 进行链接预测
pred_scores = model(test_data.x1, test_data.edge_index, test_data.edge_attr)

# 评估链接预测结果
accuracy, precision, recall, f1, roc_auc, aupr = evaluate(test_data.x2, pred_scores)
print(f'Accuracy: {accuracy} \nPrecision: {precision} \nRecall: {recall} \nF1 Score: {f1}')
print(f'ROC AUC: {roc_auc} \nAUPR: {aupr}')




import networkx as nx
import torch
from torch_geometric.data import Data


# 将 PyTorch Geometric 图数据转换为 NetworkX 图
G = nx.Graph()
G.add_nodes_from(range(test_data.num_nodes))
G.add_edges_from(test_data.edge_index.t().tolist())

# 使用 NetworkX 绘制图
pos = nx.spring_layout(G)
nx.draw(G, pos, with_labels=True, font_weight='bold', node_color='lightblue', node_size=1000, font_size=8, edge_color='gray')
plt.show()



