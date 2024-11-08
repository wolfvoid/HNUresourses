

# 例子：
m = (13 ,15 ,16 ,16 ,19 ,20 ,20 ,21 ,22 ,22 ,25 ,25 ,25 ,25 ,30 ,33 ,33 ,35 ,35 ,35 ,35 ,36 ,40 ,45 ,46 ,52,70)
total = sum(m)
count = len(m)
print("元组中所有数字的和:", total)
print("个数:", count)

import matplotlib.pyplot as plt
data = [13, 15, 16, 16, 19, 20, 20, 21, 22, 22, 25, 25, 25, 25, 30, 33, 33, 35, 35, 35, 35, 36, 40, 45, 46, 52, 70]
plt.boxplot(data)
plt.title('Box Plot of the Data')
plt.show()

import scipy.stats as stats
import matplotlib.pyplot as plt
data = [13, 15, 16, 16, 19, 20, 20, 21, 22, 22, 25, 25, 25, 25, 30, 33, 33, 35, 35, 35, 35, 36, 40, 45, 46, 52, 70]
# 计算标准正态分布的分位数
theoretical_quantiles = stats.norm.ppf([(i - 0.5) / len(data) for i in range(1, len(data) + 1)])
# 计算数据集的分位数
sample_quantiles = sorted(data)
plt.scatter(theoretical_quantiles, sample_quantiles)
plt.xlabel('Theoretical Quantiles')
plt.ylabel('Sample Quantiles')
plt.title('Q-Q Plot')
plt.show()
