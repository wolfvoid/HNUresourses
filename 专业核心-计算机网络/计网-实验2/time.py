import datetime

# 获取当前系统时间
current_time = datetime.datetime.now()

# 格式化时间，去掉秒后面的小数点
formatted_time = current_time.strftime("%Y-%m-%d %H:%M:%S")

# 打印格式化后的时间
print("当前系统时间:", formatted_time)
