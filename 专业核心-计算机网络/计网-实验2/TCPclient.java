import java.io.*;
import java.net.*;

public class TCPClient {
    public static void main(String[] args) {
        String serverHost = "localhost"; // 例如，"192.168.1.100" 或 "example.com"
        int serverPort = 16000; // 与服务器端相同的端口号

        try {
            Socket clientSocket = new Socket(serverHost, serverPort);

            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

            BufferedReader userInput = new BufferedReader(new InputStreamReader(System.in));

            String message;
            while (true) {
                System.out.print("请输入要发送的消息: ");
                message = userInput.readLine();

                if (message.equals("exit")) {
                    break;
                }

                out.println(message);

                String response = in.readLine();
                System.out.println("服务器响应: " + response);
            }

            clientSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
