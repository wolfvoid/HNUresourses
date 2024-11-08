import java.io.*;
import java.net.*;

public class TCPServer {
    public static void main(String[] args) {
        int port = 16000; // 选择一个未被占用的端口

        try {
            ServerSocket serverSocket = new ServerSocket(port);
            System.out.println("TCP服务器已启动，等待连接在端口 " + port + "...");

            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("客户端已连接: " + clientSocket.getInetAddress());

                BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

                String message;
                while ((message = in.readLine()) != null) {
                    System.out.println("接收到的数据: " + message);
                    out.println("服务器已收到您的消息");
                }

                clientSocket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
