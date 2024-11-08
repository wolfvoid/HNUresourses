import socket

def get_local_ip():
    try:
        # 创建一个socket连接到一个公共的主机来获取本机IP地址
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.connect(("8.8.8.8", 80))   #Google DNS服务器：8.8.8.8 或者 8.8.4.4
        local_ip = sock.getsockname()[0]
        sock.close()
        return local_ip
    except Exception as e:
        print("获取本机IP地址时发生错误:", str(e))
        return None

if __name__ == "__main__":
    local_ip = get_local_ip()
    if local_ip:
        print(f"本机IP地址是: {local_ip}")
    else:
        print("无法获取本机IP地址。")