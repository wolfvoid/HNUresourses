import socket
import threading
import os
import concurrent.futures
import pickle #序列化列表为字节数据
import datetime #获取系统时间

current_time = datetime.datetime.now()
time = current_time.strftime("%Y-%m-%d %H:%M:%S")
# 建立服务器并等待客户端
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # 创建服务器套接字
server_host = '10.68.223.252'  # 服务器主机
server_port = 15003 # 服务器端口
server_socket.bind((server_host, server_port))
server_socket.listen(6)
# 用于存储已连接的客户端套接字和用户名的字典
client_sockets = {}
client_usernames = {}
MAX_CONNECTIONS = 5 # 设置最大连接数
executor = concurrent.futures.ThreadPoolExecutor(max_workers=MAX_CONNECTIONS) # 创建线程池
print(f"{time} server>>等待客户端连接在 {server_host}:{server_port}...")

# 处理客户端消息的函数
def handle_client(client_socket):
    base_path = "E:\python_files\计网-实验2\服务端保存文件"
    while True:
        try:
            # 接收消息
            message = client_socket.recv(1024).decode("utf-8")
            current_time = datetime.datetime.now()
            time = current_time.strftime("%Y-%m-%d %H:%M:%S")
            if message == "/exit":  #客户端退出
                # 客户端断开连接
                del client_sockets[client_socket]
                username = client_usernames[client_socket]
                del client_usernames[client_socket]
                broadcast(f"{time} server>>>{username} 离开了聊天室")
                print(f"{time} server>>{username} 离开了聊天室")
                break
            elif message.startswith("FILE:"):   #客户端上传文件
                # 客户端要上传文件
                recv = message.split("|")
                file_name,file_size = recv[1],recv[2]
                receive_file(client_socket, file_name, file_size)
            elif message.startswith("DOWN:"):   #客户端请求下载
                # 处理文件下载请求
                recv = message.split("|")
                file_name = recv[1]
                file_path = os.path.join(base_path, file_name)
                # 请求的文件是否在本地存在
                if os.path.isfile(file_path) != True:
                    client_socket.send(f"{time} server>>错误：{file_path}：文件不存在".encode("utf-8"))
                    print(f"{time} server>>错误：{file_path}：文件不存在")
                    continue
                # 请求的文件在本地存在，开始发送
                send_requested_file(client_socket, file_name, file_path)
            elif message == "/file list":   #客户端请求查看文件列表
                file_names = list_files_in_directory(os.path.normpath(base_path))
                file_names_bytes = pickle.dumps(file_names)
                inform = "LIST:"
                client_socket.send(inform.encode("utf-8"))
                client_socket.send(file_names_bytes)
            else:
                # 否则，将消息广播给其他客户端
                username = client_usernames[client_socket]
                broadcast(f"{time} {username}: {message}")
                print(f"{time} {username}: {message}")
        except:
            # 处理异常，例如客户端断开连接
            break

# 用于接收文件的函数
def receive_file(client_socket, file_name, file_size):
    current_time = datetime.datetime.now()
    time = current_time.strftime("%Y-%m-%d %H:%M:%S")
    base_path = "E:\python_files\计网-实验2\服务端保存文件"
    save_path = os.path.join(base_path,file_name)
    try:
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
        file.close()
        print(f"{time} server>>文件上传成功")
        broadcast(f"{time} server>>>{client_usernames[client_socket]} 上传了文件: {file_name}")
    except Exception as e:
        print(f"{time} server>>>{client_usernames[client_socket]}文件传输失败: {e}")
        client_socket.send(f"{time} server>>>{client_usernames[client_socket]}文件传输失败: {e}".encode("utf-8"))  # 发送错误消息给客户端


# 处理客户端下载文件请求
def send_requested_file(client_socket, file_name, file_path):
    current_time = datetime.datetime.now()
    time = current_time.strftime("%Y-%m-%d %H:%M:%S")
    file_size = os.stat(file_path).st_size
    try:
        inform = ("FILE:" + "|" + file_name + "|" + str(file_size))
        client_socket.send(inform.encode("utf-8"))
        send_size = 0
        file = open(file_path, 'rb')
        flag = True
        while flag:
            if send_size + 1024 > file_size:
                data = file.read(file_size - send_size)
                flag = False
            else:
                data = file.read(1024)
                send_size += 1024
            client_socket.send(data)
        file.close()
        print(f"{time} server>>向 {client_usernames[client_socket]} 发送文件成功")
    except Exception as e:
        print(f"{time} server>>向 {client_usernames[client_socket]} 发送文件失败: {e}")
        client_socket.send(f"{time} server>>文件发送失败".encode("utf-8"))  # 发送错误消息给客户端


# 广播消息给所有客户端
def broadcast(message):
    for client_socket in client_sockets:
        client_socket.send(message.encode("utf-8"))

# 获取当前文件列表
def list_files_in_directory(directory):
    file_list = []
    for filename in os.listdir(directory):
        if os.path.isfile(os.path.join(directory, filename)):
            file_list.append(filename)
    return file_list

# 主循环，等待客户端连接
while True:
    current_time = datetime.datetime.now()
    time = current_time.strftime("%Y-%m-%d %H:%M:%S")
    if len(client_sockets) >= MAX_CONNECTIONS:
        # 达到最大连接数时，拒绝新连接
        client_socket, _ = server_socket.accept()
        client_socket.send(f"{time} server>>>连接已满，请稍后再试。".encode("utf-8"))
        client_socket.close()
    else:
        client_socket, client_address = server_socket.accept()
        username = client_socket.recv(1024).decode("utf-8")
        client_sockets[client_socket] = client_address
        client_usernames[client_socket] = username
        print(f"{time} server>>>连接来自 {client_address}, 用户名: {username}<<<")
        client_socket.send(f"{time} server>>>连接成功！开始聊天吧".encode("utf-8"))
        broadcast(f"{time} server>>>{username} 加入了聊天室")

        # 使用线程池处理客户端消息
        executor.submit(handle_client, client_socket)