import pandas as pd
from sklearn.feature_selection import VarianceThreshold

# 读取数据集
data = pd.read_csv('实验二数据集.tsv', delimiter='\t', index_col=0)

# 转置数据以使样本在行上，特征在列上
data = data.T

# 1. 方差阈值特征选择
variance_threshold = VarianceThreshold(threshold=0.035)  # 调整阈值
data_variance_selected = variance_threshold.fit_transform(data)

# 获取选择的列索引
selected_columns = data.columns[variance_threshold.get_support()]

# 保存选择的列名到CSV文件，以逗号分隔
selected_columns_text = ','.join(selected_columns)
with open('selected_columns.csv', 'w') as file:
    file.write(selected_columns_text)

# 输出选择的列名
print("选择的列名：")
print(selected_columns)

# 输出降维后的维度
reduced_dimension = data_variance_selected.shape[1]
print(f"降维后的维度：{reduced_dimension}")

# 保存特征选择后的数据
selected_data = pd.DataFrame(data_variance_selected, columns=selected_columns)
selected_data.to_csv('selected_data.csv', index=False)
