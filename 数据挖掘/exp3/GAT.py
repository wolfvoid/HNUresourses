import numpy as np
import pandas as pd
import torch
import torch.nn as nn
import torch.optim as optim
from sklearn.model_selection import train_test_split
from torch_geometric.data import Data
from torch_geometric.nn import GATConv

# 读取基因列表
genes_df = pd.read_csv('List_Proteins_in_SL.txt', header=None, names=['Gene'])
genes = genes_df['Gene'].tolist()

# 读取基因关系
relations_df = pd.read_csv('SL_Human_FinalCheck.txt', sep='\t', header=None, names=['Gene1', 'Gene2', 'Confidence'])
relations_df['Confidence'] = relations_df['Confidence'].astype(float)   # 转换为浮点数

# 将基因名称映射为数字标识
genes_dict = {gene: idx for idx, gene in enumerate(genes)}
relations_df['Gene1'] = relations_df['Gene1'].map(genes_dict)
relations_df['Gene2'] = relations_df['Gene2'].map(genes_dict)

# 移除带有非数字标识的行
# relations_df = relations_df.dropna(subset=['Gene1', 'Gene2'])

# 构建图的 Data 对象
edge_index = torch.tensor(relations_df[['Gene1', 'Gene2']].values.T.astype(np.int64), dtype=torch.long)
x = torch.ones((len(genes), 1))  # 每个基因有一个1维的特征
data = Data(x=x, edge_index=edge_index)


# 定义 GAT 模型
class GATModel(nn.Module):
    def __init__(self, in_features, out_features, num_heads):
        super(GATModel, self).__init__()
        self.conv1 = GATConv(in_features, out_features, heads=num_heads)

    def forward(self, data):
        x = self.conv1(data.x, data.edge_index)
        return x


# 初始化模型
model = GATModel(in_features=1, out_features=2, num_heads=1)

# 定义优化器
optimizer = optim.Adam(model.parameters(), lr=0.01)

# 划分训练集和测试集
train_mask, test_mask = train_test_split(range(len(genes)), test_size=0.2, random_state=42)

# 创建与模型输出相同形状的目标张量
target = torch.ones((len(genes), 2), dtype=torch.float)

# 训练模型（有监督）
num_epochs = 100
for epoch in range(num_epochs):
    model.train()
    optimizer.zero_grad()
    output = model(data)

    # 选择适当的有监督损失函数
    loss = nn.MSELoss()(output[train_mask], target[train_mask])  # 只使用训练集的损失进行反向传播

    loss.backward()
    optimizer.step()

    print(f'Epoch: {epoch + 1}, Loss: {loss.item()}')

# 在测试集上测试模型
model.eval()
with torch.no_grad():
    test_output = model(data)


# 可视化
# 在训练后提取节点嵌入
import matplotlib.pyplot as plt
# 在训练后提取节点嵌入
model.eval()
with torch.no_grad():
    node_embeddings = model(data).numpy()

# 获取嵌入的维度
embedding_dim = node_embeddings.shape[1]

# 根据嵌入的维度选择正确的维度进行绘图
if embedding_dim == 1:
    # 如果嵌入只有一个维度，直接绘制在x轴上
    plt.scatter(node_embeddings, np.zeros_like(node_embeddings), alpha=0.7, cmap='viridis')
else:
    # 否则，绘制散点图
    plt.scatter(node_embeddings[:, 0], node_embeddings[:, 1], alpha=0.7, cmap='viridis')

plt.title('节点嵌入')
plt.show()
