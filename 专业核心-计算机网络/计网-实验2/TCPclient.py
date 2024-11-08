import socket

# 创建TCP客户端套接字
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 服务器地址和端口
server_host = '10.68.223.252'  # 服务器主机
server_port = 15008  # 服务器端口

# 连接到服务器
client_socket.connect((server_host, server_port))

while True:
    message = input("请输入要发送的消息: ")
    if message == 'exit':
        break

    # 发送消息到服务器
    client_socket.send(message.encode('utf-8'))

    # 接收服务器的响应
    response = client_socket.recv(1024)
    print(f"服务器响应: {response.decode('utf-8')}")

# 关闭连接
client_socket.close()
