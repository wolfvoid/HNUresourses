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
# 若n_samples >= n_features,则可以调用最大似然估计法自动选择超参数
# pca = PCA(n_components="mle")
# pca_f = PCA(n_components=0.97, svd_solver="full")可以按信息量占比自动选择超参数
pca = PCA(n_components=n_components)
pca_result = pca.fit_transform(scaled_features)

# 将降维后的结果转换为DataFrame
pca_df = pd.DataFrame(data=pca_result, columns=[f'PC{i}' for i in range(1, n_components + 1)])



# 输出前N个主成分的累计方差解释比例
cumulative_variance_ratio = sum(pca.explained_variance_ratio_[:n_components])
print(f'Cumulative Variance Explained by {n_components} Principal Components: {cumulative_variance_ratio:.2%}')

# 指定要绘制的主成分
selected_components = ['PC1', 'PC2']

# 可视化降维后的数据
plt.figure(figsize=(8, 6))
plt.scatter(pca_df[selected_components[0]], pca_df[selected_components[1]], alpha=0.5)
plt.xlabel(selected_components[0])
plt.ylabel(selected_components[1])
plt.title('PCA Visualization')
plt.show()

# 选择前m个主成分
m = 3  # 选择前5个主成分
selected_pca_df = pca_df.iloc[:, :m]
# 计算相关系数矩阵
correlation_matrix = selected_pca_df.corr()
# 绘制相关系数热力图
plt.figure(figsize=(8, 6))
sns.heatmap(correlation_matrix, annot=True, cmap="coolwarm", fmt=".2f")
plt.title(f'Correlation Heatmap of the First {m} Principal Components')
plt.show()

# 绘制前m个主成分之间的散点关系图
sns.pairplot(selected_pca_df)
plt.suptitle(f'Scatter Plot of the First {m} Principal Components')
plt.show()
