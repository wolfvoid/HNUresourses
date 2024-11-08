import socket
import threading
import os
import pickle #序列化列表为字节数据
import datetime #获取系统时间

# 创建客户端套接字
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 服务器地址和端口
server_host = '10.68.223.252'  # 服务器主机
server_port = 15003  # 服务器端口
client_socket.connect((server_host, server_port))

# 输入用户名
username = input("请输入您的用户名: ")
client_socket.send(username.encode("utf-8"))

# 处理本地输入
def send_message():
    while True:
        current_time = datetime.datetime.now()
        time = current_time.strftime("%Y-%m-%d %H:%M:%S")
        message = input()
        if message.lower() == "/exit":  # 退出客户端
            client_socket.send(message.lower().encode("utf-8"))
            client_socket.close()
            break
        elif message.startswith("/file upload "):   # 上传文件
            file_path = os.path.normpath(message[13:])
            if os.path.isfile(file_path) != True:
                print(f"{time} local>>错误：{file_path}：文件不存在")
                continue
            send_file(file_path)
        elif message.startswith("/file download "): # 下载文件
            file_name = message[15:]
            download_query(file_name)
        elif message.lower() == "/file list ":  # 查看文件列表
            client_socket.send(message.lower().encode("utf-8"))
        else:   # 发送普通消息
            client_socket.send(message.encode("utf-8"))

# 上传文件
def send_file(file_path):
    current_time = datetime.datetime.now()
    time = current_time.strftime("%Y-%m-%d %H:%M:%S")
    try:
        file_name = os.path.basename(file_path)
        file_size = os.stat(file_path).st_size
        inform = ("FILE:"+"|"+file_name+"|"+str(file_size))
        client_socket.send(inform.encode("utf-8"))
        send_size = 0
        file = open(file_path,'rb')
        flag = True
        while flag:
            if send_size + 1024 > file_size:
                data = file.read(file_size-send_size)
                flag = False
            else:
                data = file.read(1024)
                send_size += 1024
            client_socket.send(data)
        file.close()
        print(f"{time} local>>文件上传成功")
    except:
        print(f"{time} local>>文件传输失败")

# 发送下载文件请求
def download_query(file_name):
    current_time = datetime.datetime.now()
    time = current_time.strftime("%Y-%m-%d %H:%M:%S")
    try:
        inform = ("DOWN:" + "|" + file_name)
        client_socket.send(inform.encode("utf-8"))
    except:
        print(f"{time} local>>下载文件请求发送失败")

def download(message):
    current_time = datetime.datetime.now()
    time = current_time.strftime("%Y-%m-%d %H:%M:%S")
    recv = message.split("|")
    # 格式("FILE:" + "|" + file_name + "|" + str(file_size))
    file_name,file_size = recv[1],recv[2]
    base_path = "E:\python_files\计网-实验2\客户端保存文件"
    save_path = os.path.join(base_path, file_name)
    recv_size = 0
    file = open(save_path, 'wb')
    flag = True
    while flag:
        if int(file_size) > recv_size:
            data = client_socket.recv(1024)
            recv_size += len(data)
            file.write(data)
        else:
            flag = False
    print(f"{time} local>>文件 {file_name} 下载成功")
    file.close()


# 创建一个线程来处理用户输入的消息
message_thread = threading.Thread(target=send_message)
message_thread.daemon = True  # 将线程设置为守护线程
message_thread.start()

# 接收并显示服务器发送的消息
while True:
    current_time = datetime.datetime.now()
    time = current_time.strftime("%Y-%m-%d %H:%M:%S")
    message = client_socket.recv(1024).decode("utf-8")
    if not message:
        # 如果消息为空，表示与服务器断开连接
        print(f"{time} local>>与服务器断开连接")
        break
    if message.startswith("FILE:"):
        download(message)
    elif message == "LIST:":
        file_names_bytes = client_socket.recv(1024)
        file_names = pickle.loads(file_names_bytes)
        if not file_names:
            print("当前服务器:无文件")
        else:
            print("当前服务器文件列表:")
            for file_name in file_names:
                print(file_name)
    else:
        print(message)