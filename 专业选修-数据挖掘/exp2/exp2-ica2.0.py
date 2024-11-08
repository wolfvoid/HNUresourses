import pandas as pd
from sklearn.decomposition import FastICA
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mutual_info_score
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
from scipy.stats import kurtosis, skew  # 导入峰度和偏度函数

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

# 计算信噪比（SNR）
# 假设第一个独立成分是信号，剩下的成分是噪声
signal_component = ica_result[:, 0]
noise_components = ica_result[:, 1:]
snr = np.mean(np.abs(signal_component) / np.std(noise_components, axis=1))
print(f'Signal-to-Noise Ratio (SNR): {snr:.2f}')

# 指定要绘制的独立成分
selected_components = ['IC1', 'IC2']
# 创建一个新列，用于标识数据行所属的部分
ica_df['Group'] = None
ica_df.loc[0:16, 'Group'] = 'MF'  # 第一部分
ica_df.loc[16:32, 'Group'] = 'METH'  # 第二部分
ica_df.loc[32:48, 'Group'] = 'GE'  # 第三部分
ica_df.loc[48:64, 'Group'] = 'CNA'  # 第四部分
# 定义颜色映射
colors = {'MF': 'red', 'METH': 'blue', 'GE': 'green', 'CNA': 'purple'}
# 根据分组使用不同颜色绘制点
plt.figure(figsize=(8, 6))
for group, color in colors.items():
    group_data = ica_df[ica_df['Group'] == group]
    plt.scatter(group_data[selected_components[0]], group_data[selected_components[1]], c=color, label=group, alpha=0.5)
plt.xlabel(selected_components[0])
plt.ylabel(selected_components[1])
plt.title('ICA Visualization with Grouping')
plt.legend()
plt.show()

"""# 选择前m个独立成分
m = 5
selected_ica_df = ica_df.iloc[:, :m]
selected_ica_df['Group'] = ica_df['Group']  # 包含 'Group' 列
# 绘制前m个独立成分之间的散点关系图，并按组分配不同颜色
sns.pairplot(selected_ica_df, hue='Group', palette=colors)
plt.suptitle(f'Scatter Plot of the First {m} Independent Components')
plt.show()"""


# 计算互信息（Mutual Information）
# 假设第一个独立成分是信号，原始信号是真实信号
true_signal = scaled_features[:, 0]
mi = mutual_info_score(true_signal, signal_component)
print(f'Mutual Information (MI) with True Signal: {mi:.4f}')

# 计算峰度和偏度
kurtosis_values = kurtosis(ica_result, axis=0)
skewness_values = skew(ica_result, axis=0)

# 创建一个DataFrame来存储结果
result_df = pd.DataFrame({'Component': ica_df.columns[:-1], 'Kurtosis': kurtosis_values, 'Skewness': skewness_values})

# 打印结果
print(result_df)