import socket
import threading

# 处理客户端连接的函数
def handle_client(client_socket, client_address):
    try:
        while True:
            data = client_socket.recv(1024)
            if not data:
                break
            print(f"来自客户端 {client_address[0]}:{client_address[1]} 的消息: {data.decode('utf-8')}")

            # 服务器处理数据逻辑（范例置空）

            # 向客户端发送响应数据
            response = "服务器已收到您的消息"
            client_socket.send(response.encode('utf-8'))
    except Exception as e:
        print(f"来自客户端 {client_address[0]}:{client_address[1]} 的连接发生异常: {str(e)}")
    finally:
        # 关闭客户端连接
        client_socket.close()

def main():
    server_host = '10.68.223.252'  # 监听所有网络接口
    server_port = 15007  # 选择一个未被占用的端口号

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((server_host, server_port))
    server.listen(5)  # 最多允许5个客户端排队等待连接

    print(f"等待客户端连接在 {server_host}:{server_port}...")

    while True:
        client_socket, client_address = server.accept()
        print(f"客户端已连接: {client_address[0]}:{client_address[1]}")

        # 创建一个新线程来处理客户端连接
        client_handler = threading.Thread(target=handle_client, args=(client_socket, client_address))
        client_handler.start()

if __name__ == "__main__":
    main()
