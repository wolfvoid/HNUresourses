import socket

# 创建UDP服务器套接字
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 服务器地址和端口
server_host = '10.68.223.252'  # 监听所有网络接口
server_port = 15002  # 端口号

# 绑定服务器地址和端口
server_socket.bind((server_host, server_port))

print(f"UDP服务器已启动，等待数据传入在 {server_host}:{server_port}...")

while True:
    # 接收客户端发送的数据
    data, client_address = server_socket.recvfrom(1024)
    print(f"接收到的数据: {data.decode('utf-8')} 来自 {client_address}")

    # 回复客户端
    response = "服务器已收到您的消息"
    server_socket.sendto(response.encode('utf-8'), client_address)
