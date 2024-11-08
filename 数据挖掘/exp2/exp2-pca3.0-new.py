import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 读取CSV文件，header=0表示有列标签
data = pd.read_csv('selected_data.csv', header=0)

# 提取特征（所有列）
features = data.iloc[:, :]

# 对特征进行标准化
scaler = StandardScaler()
scaled_features = scaler.fit_transform(features)

# 指定主成分的数量
n_components = 5  # 前五个主成分

# 创建PCA模型并进行降维
pca = PCA(n_components=n_components)
pca_result = pca.fit_transform(scaled_features)

# 将降维后的数据转换为DataFrame
pca_df = pd.DataFrame(data=pca_result, columns=[f'PC{i}' for i in range(1, n_components + 1)])

# 创建一个新列，用于标识数据行所属的部分
pca_df['Group'] = None
pca_df.loc[0:16, 'Group'] = 'MF'  # 第一部分
pca_df.loc[16:32, 'Group'] = 'METH'  # 第二部分
pca_df.loc[32:48, 'Group'] = 'GE'  # 第三部分
pca_df.loc[48:64, 'Group'] = 'CNA'  # 第四部分

# 定义颜色映射
colors = {'MF': 'red', 'METH': 'blue', 'GE': 'green', 'CNA': 'purple'}

# 指定用于三维图的主成分
selected_components = ['PC1', 'PC2', 'PC3', 'PC4', 'PC5']

# 生成所有可能的两两主成分组合
combinations = [(i, j) for i in selected_components for j in selected_components if i != j]

# 创建每个组合的三维散点图
for i, (component1, component2) in enumerate(combinations, 1):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # 根据“Group”分配不同颜色的数据点
    for group, color in colors.items():
        group_data = pca_df[pca_df['Group'] == group]
        ax.scatter(group_data[component1], group_data[component2], group_data[selected_components[2]], c=color, label=group, alpha=0.5)

    ax.set_xlabel(component1)
    ax.set_ylabel(component2)
    ax.set_zlabel(selected_components[2])
    ax.set_title(f'PCA Components {component1}, {component2} vs. {selected_components[2]}')
    ax.legend()

plt.show()
