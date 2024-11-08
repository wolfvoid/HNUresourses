from sklearn.cluster import KMeans
import numpy as np
from sklearn.preprocessing import StandardScaler

data = np.array([5, 10, 11, 13, 15, 35, 50, 55, 72, 92, 204, 215])

# 将数据转换为一列
data = data.reshape(-1, 1)

# 标准化数据
scaler = StandardScaler()
data_scaled = scaler.fit_transform(data)

kmeans = KMeans(n_clusters=3, algorithm='auto').fit(data_scaled)
labels = kmeans.labels_

# 使用逆变换将标准化后的聚类中心转换为原始值
cluster_centers_original = scaler.inverse_transform(kmeans.cluster_centers_)

# 输出聚类中心的原始值
print("聚类中心的原始值:")
for center in cluster_centers_original:
    print(center)

# 根据标签将标准化后的数据点分为三个簇
cluster1_scaled = data_scaled[labels == 0]
cluster2_scaled = data_scaled[labels == 1]
cluster3_scaled = data_scaled[labels == 2]

# 使用逆变换将标准化后的数据点转换为原始值
cluster1_original = scaler.inverse_transform(cluster1_scaled)
cluster2_original = scaler.inverse_transform(cluster2_scaled)
cluster3_original = scaler.inverse_transform(cluster3_scaled)

print("簇1（原始值）:", cluster1_original)
print("簇2（原始值）:", cluster2_original)
print("簇3（原始值）:", cluster3_original)
