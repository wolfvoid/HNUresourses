import pandas as pd
import umap
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # 导入3D绘图模块
from sklearn.preprocessing import StandardScaler

# 读取CSV文件，header=None表示没有列标签
data = pd.read_csv('selected_data.csv', header=0)

# 提取特征（所有列）
features = data.iloc[:, :]

# 对特征进行标准化
scaled_features = StandardScaler().fit_transform(features)

# 创建UMAP模型并进行降维
n_components = 3  # 降维后的维度
umap_model = umap.UMAP(n_neighbors=4, n_components=n_components)
umap_result = umap_model.fit_transform(scaled_features)

# 将降维后的结果转换为DataFrame
umap_df = pd.DataFrame(data=umap_result, columns=[f'UMAP{i}' for i in range(1, n_components + 1)])

# 指定要绘制的UMAP成分
selected_components = ['UMAP1', 'UMAP2', 'UMAP3']  # 选择三个成分

# 创建一个新列，用于标识数据行所属的部分
umap_df['Group'] = None
umap_df.loc[0:16, 'Group'] = 'MF'  # 第一部分
umap_df.loc[16:32, 'Group'] = 'METH'  # 第二部分
umap_df.loc[32:48, 'Group'] = 'GE'  # 第三部分
umap_df.loc[48:64, 'Group'] = 'CNA'  # 第四部分

# 定义颜色映射
colors = {'MF': 'red', 'METH': 'blue', 'GE': 'green', 'CNA': 'purple'}

# 创建一个三维坐标轴
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# 根据分组使用不同颜色绘制点
for group, color in colors.items():
    group_data = umap_df[umap_df['Group'] == group]
    ax.scatter(group_data[selected_components[0]], group_data[selected_components[1]], group_data[selected_components[2]], c=color, label=group, alpha=0.5)

ax.set_xlabel(selected_components[0])
ax.set_ylabel(selected_components[1])
ax.set_zlabel(selected_components[2])
ax.set_title('UMAP 3D Visualization with Grouping')
plt.legend()
plt.show()
