import time
import serial
import serial.tools.list_ports
import tkinter as tk
from tkinter import Label, PhotoImage
import threading
from PIL import Image, ImageTk  # 导入PIL库中的Image和ImageTk模块

# 字节转字符串
def b2s(data):
    return ''.join([f'{ch:0>2x}' for ch in data]).upper()

# 连接设备
ser = serial.Serial(list(serial.tools.list_ports.comports()[0])[0], 1200)
# 判断是否连接到设备
assert(ser != None)

#第一次互相通信
startData = b'\xaa\x55\x00\x00\x00\x00'
while 1:
    ser.write(startData)
    print("向STC板发送通信申请")
    data = ser.read_all()
    sdata = b2s(data)
    print(sdata)
    if sdata[:12] == "AA55A1A1A1A1":
        print("通信成功")
        break
    print("通信失败")

# 线程，用于在通信成功时更新可视化窗口的数据
def update_data_label(data_label, image_label):
    while True:
        time.sleep(1)
        data = ser.read_all()
        sdata = b2s(data)
        if sdata[:4] == "AA55":
            print("通信成功")
            print(sdata)
            fifth_value = sdata[4]
            sixth_value = sdata[5]
            data_label.config(text=f"通信正常，模式信息{fifth_value,sixth_value}", font=("Helvetica", 16))

            # 设置图像文件路径
            image_path = ""

            #正常模式
            if fifth_value == '0':
                if sixth_value == '1':
                    image_path = "mode1.png"
                elif sixth_value == '2':
                    image_path = "mode2.png"
                elif sixth_value == '3':
                    image_path = "mode3.png"
                elif sixth_value == '4':
                    image_path = "mode4.png"
                elif sixth_value == '5':
                    image_path = "mode5.png"
                elif sixth_value == '6':
                    image_path = "mode6.png"
                elif sixth_value == '7':
                    image_path = "mode7.png"
            #震动恢复模式
            elif sixth_value == '0':
                if fifth_value == '1':
                    image_path = "vib_choose_mode.png"
                elif fifth_value == '2':
                    image_path = "vib_welcome.png"
                elif fifth_value == '3':
                    image_path = "vib_mode1.png"
                elif fifth_value == '4':
                    image_path = "vib_mode2.png"
                elif fifth_value == '5':
                    image_path = "vib_mode3.png"
                elif fifth_value == '6':
                    image_path = "vib_mode4.png"
                elif fifth_value == '7':
                    image_path = "vib_mode5.png"
                elif fifth_value == '8':
                    image_path = "vib_mode6.png"
                elif fifth_value == '9':
                    image_path = "vib_mode7.png"
            #选择模式
            elif sixth_value == 'A':
                if fifth_value == '3':
                    image_path = "choose_mode1.png"
                elif fifth_value == '4':
                    image_path = "choose_mode2.png"
                elif fifth_value == '5':
                    image_path = "choose_mode3.png"
                elif fifth_value == '6':
                    image_path = "choose_mode4.png"
                elif fifth_value == '7':
                    image_path = "choose_mode5.png"
                elif fifth_value == '8':
                    image_path = "choose_mode6.png"
                elif fifth_value == '9':
                    image_path = "choose_mode7.png"
            if image_path:
                # 使用PIL库加载图像
                image = Image.open(image_path)

                # 获取窗口大小
                window_width = 1200 #window.winfo_width()
                window_height = 800 #window.winfo_height()

                # 根据窗口大小调整图像大小并保持比例
                image.thumbnail((window_width, window_height))

                # 将图像转换为Tkinter PhotoImage对象
                tk_image = ImageTk.PhotoImage(image)

                # 更新图像标签
                image_label.config(image=tk_image)
                image_label.image = tk_image
            """else:
                # 清空图片
                print("通信出错")
                my_image = PhotoImage(file="error.png")
                image_label.config(image=my_image)"""

# 创建一个窗口
window = tk.Tk()
window.title("STC模型PC端用户端学习引导程序@甘晴void")
window.geometry("1200x800")  # 设置窗口大小

# 创建一个标签用于显示数据
data_label = tk.Label(window, text="", font=("Helvetica", 16))
data_label.pack()

# 创建一个标签用于显示图片
my_image = PhotoImage(file="welcome.png")
image_label = Label(window, image=my_image)
image_label.pack()

# 创建一个线程来更新数据标签
update_thread = threading.Thread(target=update_data_label, args=(data_label, image_label))
update_thread.daemon = True
update_thread.start()

window.mainloop()