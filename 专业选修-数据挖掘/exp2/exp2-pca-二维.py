import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
import seaborn as sns


# 读取CSV文件，header=None表示没有列标签
data = pd.read_csv('selected_data.csv', header=0)

# 提取特征（所有列）
features = data.iloc[:, :]

# 对特征进行标准化
scaler = StandardScaler()
scaled_features = scaler.fit_transform(features)

# 指定降维后的维度
n_components = 14  # 降维后的维度

# 创建PCA模型并进行降维
pca = PCA(n_components=n_components)
pca_result = pca.fit_transform(scaled_features)

# 将降维后的结果转换为DataFrame
pca_df = pd.DataFrame(data=pca_result, columns=[f'PC{i}' for i in range(1, n_components + 1)])

# 输出每一个主成分的方差解释比例
explained_variance_ratios = pca.explained_variance_ratio_
for i, explained_variance_ratio in enumerate(explained_variance_ratios, 1):
    print(f'Explained Variance Ratio for PC{i}: {explained_variance_ratio:.10%}')

# 输出前N个主成分的累计方差解释比例
cumulative_variance_ratio = sum(pca.explained_variance_ratio_[:n_components])
print(f'Cumulative Variance Explained by {n_components} Principal Components: {cumulative_variance_ratio:.2%}')

# 指定要绘制的主成分
selected_components = ['PC1', 'PC2']

# 创建一个新列，用于标识数据行所属的部分
pca_df['Group'] = None
pca_df.loc[0:16, 'Group'] = 'MF'  # 第一部分
pca_df.loc[16:32, 'Group'] = 'METH'  # 第二部分
pca_df.loc[32:48, 'Group'] = 'GE'  # 第三部分
pca_df.loc[48:64, 'Group'] = 'CNA'  # 第四部分

# 定义颜色映射
colors = {'MF': 'red', 'METH': 'blue', 'GE': 'green', 'CNA': 'purple'}

# 根据分组使用不同颜色绘制点
plt.figure(figsize=(8, 6))
for group, color in colors.items():
    group_data = pca_df[pca_df['Group'] == group]
    plt.scatter(group_data[selected_components[0]], group_data[selected_components[1]], c=color, label=group, alpha=0.5)

plt.xlabel(selected_components[0])
plt.ylabel(selected_components[1])
plt.title('PCA Visualization with Grouping')
plt.legend()
plt.show()

# 选择前m个主成分
m = 5
selected_pca_df = pca_df.iloc[:, :m]
selected_pca_df['Group'] = pca_df['Group']  # 包含 'Group' 列

"""# 绘制相关系数热力图
# 计算相关系数矩阵
correlation_matrix = selected_pca_df.corr()
plt.figure(figsize=(8, 6))
sns.heatmap(correlation_matrix, annot=True, cmap="coolwarm", fmt=".2f")
plt.title(f'Correlation Heatmap of the First {m} Principal Components')
plt.show()"""

# 绘制前m个主成分之间的散点关系图，并按组分配不同颜色
sns.pairplot(selected_pca_df, hue='Group', palette=colors)
plt.suptitle(f'Scatter Plot of the First {m} Principal Components')
plt.show()

#将PCA降维的结果保存，以便后续t-SNE的操作
# 将降维后的结果转换为DataFrame
pca_df = pd.DataFrame(data=pca_result, columns=[f'PC{i}' for i in range(1, n_components + 1)])
# 保存PCA降维后的数据到CSV文件
pca_df.to_csv('pca_processed.csv', index=False)