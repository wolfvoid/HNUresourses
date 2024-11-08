from mpl_toolkits.mplot3d import Axes3D  # 导入3D绘图库
import pandas as pd
from sklearn.decomposition import FastICA
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt


# 读取CSV文件，header=None表示没有列标签
data = pd.read_csv('selected_data.csv', header=0)

# 提取特征（所有列）
features = data.iloc[:, :]

# 对特征进行标准化
scaler = StandardScaler()
scaled_features = scaler.fit_transform(features)

# 指定降维后的维度
n_components = 3  # 降维后的维度

# 创建ICA模型并进行降维
ica = FastICA(n_components=n_components)
ica_result = ica.fit_transform(scaled_features)

# 将降维后的结果转换为DataFrame
ica_df = pd.DataFrame(data=ica_result, columns=[f'IC{i}' for i in range(1, n_components + 1)])

# 创建一个新列，用于标识数据行所属的部分
ica_df['Group'] = None
ica_df.loc[0:16, 'Group'] = 'MF'  # 第一部分
ica_df.loc[16:32, 'Group'] = 'METH'  # 第二部分
ica_df.loc[32:48, 'Group'] = 'GE'  # 第三部分
ica_df.loc[48:64, 'Group'] = 'CNA'  # 第四部分

# 定义颜色映射
colors = {'MF': 'red', 'METH': 'blue', 'GE': 'green', 'CNA': 'purple'}

# 选择要绘制的独立成分
selected_components = ['IC1', 'IC2', 'IC3']

# 创建一个新的三维图
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# 根据分组使用不同颜色绘制点
for group, color in colors.items():
    group_data = ica_df[ica_df['Group'] == group]
    ax.scatter(group_data[selected_components[0]], group_data[selected_components[1]], group_data[selected_components[2]], c=color, label=group, alpha=0.5)

ax.set_xlabel(selected_components[0])
ax.set_ylabel(selected_components[1])
ax.set_zlabel(selected_components[2])
ax.set_title('ICA 3D Visualization with Grouping')
ax.legend()

plt.show()
