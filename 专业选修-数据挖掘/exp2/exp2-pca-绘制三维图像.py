import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
import seaborn as sns
from mpl_toolkits.mplot3d import Axes3D

# 读取CSV文件，header=0表示有列标签
data = pd.read_csv('selected_data.csv', header=0)

# 提取特征（所有列）
features = data.iloc[:, :]

# 对特征进行标准化
scaler = StandardScaler()
scaled_features = scaler.fit_transform(features)

# 指定主成分的数量
n_components = 3  # 3D图

# 创建PCA模型并进行降维
pca = PCA(n_components=n_components)
pca_result = pca.fit_transform(scaled_features)

# 将降维后的数据转换为DataFrame
pca_df = pd.DataFrame(data=pca_result, columns=[f'PC{i}' for i in range(1, n_components + 1)])

# 输出前三个主成分的方差解释比例
explained_variance_ratios = pca.explained_variance_ratio_
for i, explained_variance_ratio in enumerate(explained_variance_ratios, 1):
    print(f'主成分{i}的方差解释比例: {explained_variance_ratio:.10%}')

# 输出前三个主成分的累积方差解释比例
cumulative_variance_ratio = sum(pca.explained_variance_ratio_[:n_components])
print(f'前{cumulative_variance_ratio:.2%}的主成分累积方差解释比例')

# 创建一个新列，用于标识数据行所属的部分
pca_df['Group'] = None
pca_df.loc[0:16, 'Group'] = 'MF'  # 第一部分
pca_df.loc[16:32, 'Group'] = 'METH'  # 第二部分
pca_df.loc[32:48, 'Group'] = 'GE'  # 第三部分
pca_df.loc[48:64, 'Group'] = 'CNA'  # 第四部分

# 定义颜色映射
colors = {'MF': 'red', 'METH': 'blue', 'GE': 'green', 'CNA': 'purple'}

# 指定用于三维图的主成分
selected_components = ['PC1', 'PC2', 'PC3']

# 创建一个三维散点图
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# 根据“Group”分配不同颜色的数据点
for group, color in colors.items():
    group_data = pca_df[pca_df['Group'] == group]
    ax.scatter(group_data[selected_components[0]], group_data[selected_components[1]], group_data[selected_components[2]], c=color, label=group, alpha=0.5)

ax.set_xlabel(selected_components[0])
ax.set_ylabel(selected_components[1])
ax.set_zlabel(selected_components[2])
ax.set_title('PCA可视化三维图')
ax.legend(loc='upper left', bbox_to_anchor=(1.0, 1.0))  #调整图例位置
ax.legend()
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.show()
