import socket
import concurrent.futures
import threading

# 最大允许的客户端连接数
MAX_CLIENTS = 5

# 存储当前活跃客户端连接的列表
active_clients = []

# 线程锁用于保护 active_clients 列表
count_lock = threading.Lock()

# 全局计数器用于跟踪已连接的客户端数量
connected_clients = 0


# 处理客户端连接的函数
def handle_client(client_socket, client_address):
    global connected_clients

    try:
        with count_lock:
            connected_clients += 1
            #print(f"connected_clients= {connected_clients} ")
            if connected_clients > MAX_CLIENTS:
                # 如果连接数超过最大限制，向客户端发送拒绝通知
                print("服务器连接已满，已拒绝一个新的连接")
                response = "服务器连接已满，拒绝连接。"
                client_socket.send(response.encode('utf-8'))
                return
            else:
                active_clients.append(client_socket)

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
        with count_lock:
            connected_clients -= 1
            active_clients.remove(client_socket)
            client_socket.close()


def main():
    server_host = '10.68.223.252'  # 监听所有网络接口
    server_port = 15008  # 选择一个未被占用的端口号

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((server_host, server_port))
    server.listen(MAX_CLIENTS+1)  # 最多允许5个客户端排队等待连接

    print(f"等待客户端连接在 {server_host}:{server_port}...")

    # 创建一个线程池
    with concurrent.futures.ThreadPoolExecutor(max_workers=MAX_CLIENTS+1) as executor:
        while True:
            client_socket, client_address = server.accept()
            print(f"客户端已连接: {client_address[0]}:{client_address[1]}")

            # 使用线程池处理客户端连接
            executor.submit(handle_client, client_socket, client_address)


if __name__ == "__main__":
    main()
