import numpy as np
import pandas as pd
import torch
import torch.nn as nn
import torch.optim as optim
from torch_geometric.data import Data
from torch_geometric.nn import GATConv
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt

# 读取基因列表
genes_df = pd.read_csv('List_Proteins_in_SL.txt', header=None, names=['Gene'])
genes = genes_df['Gene'].tolist()

# 读取基因关系
relations_df = pd.read_csv('SL_Human_FinalCheck.txt', sep='\t', header=None, names=['Gene1', 'Gene2', 'Confidence'])
relations_df['Confidence'] = relations_df['Confidence'].astype(float)

# 将基因名称映射为数字标识
genes_dict = {gene: idx for idx, gene in enumerate(genes)}
relations_df['Gene1'] = relations_df['Gene1'].map(genes_dict)
relations_df['Gene2'] = relations_df['Gene2'].map(genes_dict)

# 移除带有非数字标识的行
relations_df = relations_df.dropna(subset=['Gene1', 'Gene2', 'Confidence'])

# 构建图的 Data 对象
edge_index = torch.tensor(relations_df[['Gene1', 'Gene2']].values.T.astype(np.int64), dtype=torch.long)
x = torch.ones((len(genes), 1))  # 每个基因有一个1维的特征
y = torch.tensor(relations_df['Confidence'].values, dtype=torch.float).view(-1, 1)  # 置信分数作为目标

data = Data(x=x, edge_index=edge_index, y=y)

# 定义GAT模型
class GATModel(nn.Module):
    def __init__(self, in_features, out_features, num_heads):
        super(GATModel, self).__init__()
        self.conv1 = GATConv(in_features, out_features, heads=num_heads)

    def forward(self, data):
        x = self.conv1(data.x, data.edge_index)
        return x

# 初始化模型
model = GATModel(in_features=1, out_features=1, num_heads=1)

# 定义优化器
optimizer = optim.Adam(model.parameters(), lr=0.01)

# 回归任务的损失函数
loss_function = nn.MSELoss()

# 划分训练集和测试集
train_mask, test_mask = train_test_split(range(len(genes)), test_size=0.2, random_state=42)

# 训练模型（回归任务）
num_epochs = 200
losses = []  # 用于存储每个epoch的损失值

for epoch in range(num_epochs):
    model.train()
    optimizer.zero_grad()
    output = model(data)

    # 使用均方误差损失
    loss = loss_function(output[train_mask], data.y[train_mask])
    loss.backward()
    optimizer.step()

    losses.append(loss.item())  # 记录每个epoch的损失值
    print(f'Epoch: {epoch + 1}, Loss: {loss.item()}')

# 在测试集上测试模型
model.eval()
with torch.no_grad():
    test_output = model(data)


# 绘制损失率的曲线图
plt.plot(losses, label='Training Loss')
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.title('Training Loss Over Time')
plt.legend()
plt.show()


# 评估模型性能
# 在测试集上计算性能指标
from sklearn.metrics import mean_squared_error, mean_absolute_error

model.eval()
with torch.no_grad():
    test_output = model(data)

# 将tensor转换为numpy数组
test_output_np = test_output.cpu().numpy()
y_true_np = data.y[test_mask].cpu().numpy()

# 将test_output_np和y_true_np调整为相同的样本数
test_output_np = test_output[test_mask].cpu().numpy()

# 计算均方根误差和平均绝对误差
rmse = np.sqrt(mean_squared_error(y_true_np, test_output_np))
mae = mean_absolute_error(y_true_np, test_output_np)

print(f'Root Mean Squared Error (RMSE): {rmse}')
print(f'Mean Absolute Error (MAE): {mae}')


# 散点图（Scatter Plot）
plt.scatter(y_true_np, test_output_np)
plt.xlabel('Actual Values')
plt.ylabel('Predicted Values')
plt.title('Scatter Plot of Actual vs Predicted Values')
plt.show()


# 残差图（Residual Plot）
residuals = y_true_np - test_output_np
plt.scatter(y_true_np, residuals)
plt.xlabel('Actual Values')
plt.ylabel('Residuals')
plt.axhline(y=0, color='r', linestyle='--', linewidth=2)  # 添加水平线表示残差为零
plt.title('Residual Plot')
plt.show()
