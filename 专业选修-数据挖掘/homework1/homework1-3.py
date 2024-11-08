
#给定数据
data = [200, 300, 400, 600, 1000]

# 最小-最大规范化
min_val = min(data)
max_val = max(data)
normalized_data = [(x - min_val) / (max_val - min_val) for x in data]
#print(normalized_data)
print([round(val, 2) for val in normalized_data])  # 保留两位小数

#  z 分数规范化，使用标准差
import statistics
mean = statistics.mean(data)
std_dev = statistics.stdev(data)
z_scores = [(x - mean) / std_dev for x in data]
#print(z_scores)
print([round(val, 2) for val in z_scores])  # 保留两位小数


# z 分数规范化，使用均值绝对偏差
def mean_absolute_deviation(data):
    mean = sum(data) / len(data)
    deviation = [abs(x - mean) for x in data]
    return sum(deviation) / len(deviation)

mad = mean_absolute_deviation(data)
normalized_data = [(x - statistics.mean(data)) / mad for x in data]
#print(normalized_data)
print([round(val, 2) for val in normalized_data])

# 小数定标规范化
max_val = max(data)
num_digits = len(str(max_val))
scaled_data = [x / (max_val) for x in data]
#print(scaled_data)
print([round(val, 2) for val in scaled_data]) # 保留两位小数
