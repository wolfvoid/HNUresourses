from sklearn.cluster import KMeans
import numpy as np
from sklearn.preprocessing import StandardScaler

data = np.array([5, 10, 11, 13, 15, 35, 50, 55, 72, 92, 204, 215])
data = data.reshape(-1, 1)  # 将数据转换为一列

"""# 标准化数据
scaler = StandardScaler()
data = scaler.fit_transform(data)"""

kmeans = KMeans(n_clusters=3, algorithm='lloyd').fit(data)
print(kmeans)
labels = kmeans.labels_

# 根据标签将数据点分为三个簇
cluster1 = data[labels == 0]
cluster2 = data[labels == 1]
cluster3 = data[labels == 2]

print("簇1:", cluster1)
print("簇2:", cluster2)
print("簇3:", cluster3)

# 打印每个簇的中心点位置
centers = kmeans.cluster_centers_
print("簇1 中心点:", centers[0])
print("簇2 中心点:", centers[1])
print("簇3 中心点:", centers[2])