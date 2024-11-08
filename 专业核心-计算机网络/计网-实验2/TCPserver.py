import socket

# 创建TCP服务器套接字
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 绑定服务器地址和端口
server_host = '10.68.223.252'  # 服务器主机
server_port = 15001  # 服务器端口
server_socket.bind((server_host, server_port))

# 开始监听客户端连接
server_socket.listen(1)  # 最多允许一个客户端连接

print(f"等待客户端连接在 {server_host}:{server_port}...")
client_socket, client_address = server_socket.accept()
print(f"连接来自: {client_address}")

while True:
    # 接收客户端发送的数据
    data = client_socket.recv(1024)
    if not data:
        break
    print(f"接收到的数据: {data.decode('utf-8')}")

    # 回复客户端
    response = "服务器已收到您的消息"
    client_socket.send(response.encode('utf-8'))

# 关闭连接
client_socket.close()
server_socket.close()
