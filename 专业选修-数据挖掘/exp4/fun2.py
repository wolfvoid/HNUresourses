import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import Dataset, DataLoader
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score, classification_report
import pandas as pd
import numpy as np

# 定义 GCN 模型
class GCN(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(GCN, self).__init__()
        self.layer1 = nn.Linear(input_size, hidden_size)
        self.layer2 = nn.Linear(hidden_size, output_size)
        self.relu = nn.ReLU()
        self.sigmoid = nn.Sigmoid()

    def forward(self, x):
        x = self.relu(self.layer1(x))
        x = self.sigmoid(self.layer2(x))  # 使用 sigmoid 将输出限制在 0 到 1 之间
        return x


# 自定义数据集类
class LinkDataset(Dataset):
    def __init__(self, features, labels):
        self.features = torch.tensor(features, dtype=torch.float32)
        self.labels = torch.tensor(labels.values, dtype=torch.float32)

    def __len__(self):
        return len(self.features)

    def __getitem__(self, idx):
        return self.features[idx], self.labels[idx]

# 读取数据
gene_list = pd.read_csv('GeneList.txt', header=None, names=['Gene'])
positive_links = pd.read_csv('Positive_LinkSL.txt', delimiter='\t', header=None,
                             names=['Gene1', 'Gene2', 'Confidence'], dtype={'Gene1': str})
feature_ppi = pd.read_csv('Feature2_ppi.txt', delimiter=' ', header=None,
                          names=[f'ppi_feature_{i}' for i in range(128)], dtype={'Gene1': str})
feature_go = pd.read_csv('Feature1_go.txt', delimiter=' ', header=None,
                         names=[f'go_feature_{i}' for i in range(128)])
network_data = pd.read_csv('Network1_SL.txt', delimiter='\s+', header=None, names=['Gene1', 'Gene2', 'Network1'])

# 重新定义特征和标签，只选择数值类型的列
data = pd.concat([positive_links, feature_ppi, feature_go, network_data], axis=1)

# 打印一些样本数据
print("Sample data:")
print(data.head())

# 填充NaN值
data.fillna(0, inplace=True)

# 重新定义特征和标签，只选择数值类型的列
numeric_columns = data.select_dtypes(include=np.number).columns
X = data.loc[:, numeric_columns]

# 打印一些样本特征
print("Sample features:")
print(X.head())

y = data['Confidence'].apply(lambda x: 1 if x > 0 else 0)

# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 标准化特征
scaler = StandardScaler()
X_train_numeric_scaled = scaler.fit_transform(X_train)
X_test_numeric_scaled = scaler.transform(X_test)

# 定义和训练 GCN 模型
input_size = X_train_numeric_scaled.shape[1]
hidden_size = 64
output_size = 1
model = GCN(input_size, hidden_size, output_size)
criterion = nn.BCELoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

# 转换为 PyTorch DataLoader
train_dataset = LinkDataset(X_train_numeric_scaled, y_train)
train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)

# 训练模型
num_epochs = 20
for epoch in range(num_epochs):
    for inputs, labels in train_loader:
        optimizer.zero_grad()
        outputs = model(inputs)
        loss = criterion(outputs, labels.unsqueeze(1))
        loss.backward()
        optimizer.step()
    print(loss.item())

# 在测试集上进行预测
X_test_tensor = torch.tensor(X_test_numeric_scaled, dtype=torch.float32)
with torch.no_grad():
    model.eval()
    predictions = model(X_test_tensor).numpy()
    predictions_binary = np.round(predictions)

# 评估模型性能
accuracy = accuracy_score(y_test, predictions_binary)
print("Accuracy:", accuracy)
print("Classification Report:\n", classification_report(y_test, predictions_binary))
