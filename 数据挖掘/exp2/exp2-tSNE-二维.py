import pandas as pd
from sklearn.manifold import TSNE
import matplotlib.pyplot as plt
import seaborn as sns

# 读取CSV文件，header=None表示没有列标签
data = pd.read_csv('pca_processed.csv', header=0)

# 提取特征（所有列）
features = data.iloc[:, :]

# 创建t-SNE模型并进行降维
n_components = 2  # 降维后的维度
tsne_model = TSNE(n_components=n_components, random_state=7)
tsne_result = tsne_model.fit_transform(features)

# 将降维后的结果转换为DataFrame
tsne_df = pd.DataFrame(data=tsne_result, columns=[f't-SNE{i}' for i in range(1, n_components + 1)])

# 指定要绘制的t-SNE成分
selected_components = ['t-SNE1', 't-SNE2']

# 创建一个新列，用于标识数据行所属的部分
tsne_df['Group'] = None
tsne_df.loc[0:16, 'Group'] = 'MF'  # 第一部分
tsne_df.loc[16:32, 'Group'] = 'METH'  # 第二部分
tsne_df.loc[32:48, 'Group'] = 'GE'  # 第三部分
tsne_df.loc[48:64, 'Group'] = 'CNA'  # 第四部分

# 定义颜色映射
colors = {'MF': 'red', 'METH': 'blue', 'GE': 'green', 'CNA': 'purple'}

# 根据分组使用不同颜色绘制点
plt.figure(figsize=(8, 6))
for group, color in colors.items():
    group_data = tsne_df[tsne_df['Group'] == group]
    plt.scatter(group_data[selected_components[0]], group_data[selected_components[1]], c=color, label=group, alpha=0.5)

plt.xlabel(selected_components[0])
plt.ylabel(selected_components[1])
plt.title('t-SNE Visualization with Grouping')
plt.legend()
plt.show()
