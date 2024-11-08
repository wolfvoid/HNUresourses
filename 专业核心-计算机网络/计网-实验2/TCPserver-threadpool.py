import socket
import concurrent.futures

# 处理客户端连接的函数
def handle_client(client_socket, client_address):
    try:
        while True:
            data = client_socket.recv(1024)
            if not data:
                break
            print(f"客户端 {client_address[0]}:{client_address[1]} 发来数据: {data.decode('utf-8')}")

            # 服务器处理数据逻辑（范例置空）

            # 向客户端发送响应数据
            response = "服务器已收到您的消息"
            client_socket.send(response.encode('utf-8'))
    except Exception as e:
        print(f"发生异常: {str(e)}")
    finally:
        # 关闭客户端连接
        client_socket.close()

def main():
    server_host = '192.168.1.110'  # 服务器主机
    server_port = 15004  # 服务器端口

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((server_host, server_port))
    server.listen(5)  # 最多允许5个客户端排队等待连接

    print(f"等待客户端连接在 {server_host}:{server_port}...")

    # 创建一个线程池
    with concurrent.futures.ThreadPoolExecutor(max_workers=5) as executor:
        while True:
            client_socket, client_address = server.accept()
            print(f"客户端已连接: {client_address[0]}:{client_address[1]}")

            # 使用线程池处理客户端连接
            executor.submit(handle_client, client_socket, client_address)

if __name__ == "__main__":
    main()
