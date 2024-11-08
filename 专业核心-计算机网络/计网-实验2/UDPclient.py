import socket

# 创建UDP客户端套接字
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 服务器地址和端口
server_host = '10.68.223.252'  #
server_port = 15002  # 与服务器端相同的端口号

while True:
    message = input("请输入要发送的消息: ")
    if message == 'exit':
        break

    # 发送消息到服务器
    client_socket.sendto(message.encode('utf-8'), (server_host, server_port))

    # 接收服务器的响应
    data, server_address = client_socket.recvfrom(1024)
    print(f"服务器响应: {data.decode('utf-8')} 来自 {server_address}")

# 关闭连接
client_socket.close()
