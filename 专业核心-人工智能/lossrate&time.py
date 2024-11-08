import re
import matplotlib.pyplot as plt

# 读取 log 文件
with open("log.txt", "r") as file:
    lines = file.readlines()

# 初始化列表来存储损失率和总耗时
losses = []
times = []

# 匹配损失率和总耗时的正则表达式
loss_pattern = re.compile(r"loss is (\d+\.\d+(?:e[-+]?\d+)?)")
time_pattern = re.compile(r"epoch time: (\d+\.\d+)")

# 提取损失率和总耗时
for line in lines:
    loss_match = loss_pattern.search(line)
    time_match = time_pattern.search(line)
    if loss_match:
        losses.append(float(loss_match.group(1)))
    if time_match:
        times.append(float(time_match.group(1)))

print(losses)
print(times)

# 绘制损失率随 epoch 变化图像
plt.figure(figsize=(10, 5))
plt.plot(losses, marker='o', color='b', label='Loss')
plt.title('Loss Rate vs Epoch')
plt.xlabel('Epoch')
plt.ylabel('Loss Rate')
plt.grid(True)
plt.legend()
plt.show()

# 绘制总耗时随 epoch 变化图像
plt.figure(figsize=(10, 5))
plt.plot(times, marker='o', color='r', label='Total Time (ms)')
plt.title('Total Time vs Epoch')
plt.xlabel('Epoch')
plt.ylabel('Total Time (ms)')
plt.grid(True)
plt.legend()
plt.show()
