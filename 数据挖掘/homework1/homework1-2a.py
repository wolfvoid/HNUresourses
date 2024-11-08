import numpy as np

# 数据集
data = np.array([[1.5, 1.7],
                 [2.0, 1.9],
                 [1.6, 1.8],
                 [1.2, 1.5],
                 [1.5, 1.0]])

# 查询点
query_point = np.array([1.4, 1.6])

# a. 使用不同相似性度量对数据点进行排名

# 欧几里得距离
euclidean_distances = np.sqrt(np.sum((data - query_point) ** 2, axis=1))
euclidean_ranking = np.argsort(euclidean_distances)

# 曼哈顿距离
manhattan_distances = np.sum(np.abs(data - query_point), axis=1)
manhattan_ranking = np.argsort(manhattan_distances)

# 上确界距离
supremum_distances = np.max(np.abs(data - query_point), axis=1)
supremum_ranking = np.argsort(supremum_distances)

# 余弦相似性
cosine_similarities = np.dot(data, query_point) / (np.linalg.norm(data, axis=1) * np.linalg.norm(query_point))
cosine_ranking = np.argsort(cosine_similarities)[::-1]  # 使用负值排名，因为余弦相似性越大越相似

# 计算值
print("欧几里得距离计算值:", euclidean_distances)
print("曼哈顿距离计算值:", manhattan_distances)
print("上确界距离计算值:", supremum_distances)
print("余弦相似性计算值:", cosine_similarities)

# 打印排名结果
print("欧几里得距离排名:", euclidean_ranking + 1)  # 加1以匹配数据点的索引
print("曼哈顿距离排名:", manhattan_ranking + 1)
print("上确界距离排名:", supremum_ranking + 1)
print("余弦相似性排名:", cosine_ranking + 1)
