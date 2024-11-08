import numpy as np

# 数据集
data = np.array([[1.5, 1.7],
                 [2.0, 1.9],
                 [1.6, 1.8],
                 [1.2, 1.5],
                 [1.5, 1.0]])

# 计算每个数据点的范数
norms = np.linalg.norm(data, axis=1)

# 规格化数据集
normalized_data = data / norms[:, np.newaxis]

# 查询点，需要进行规格化
query_point = np.array([1.4, 1.6])

# 规格化查询点
query_point_norm = np.linalg.norm(query_point)
normalized_query_point = query_point / query_point_norm

# 使用欧几里得距离对规格化后的数据点进行排名
euclidean_distances = np.linalg.norm(normalized_data - normalized_query_point, axis=1)
euclidean_ranking = np.argsort(euclidean_distances)

# 打印欧几里得距离计算值和排名
print("欧几里得距离计算值:", euclidean_distances)
print("欧几里得距离排名:", euclidean_ranking + 1)  # 加1以匹配数据点的索引
