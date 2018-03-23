package com.left.tcp;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * 服务器端
 * @author left
 *
 */
public class Server {
	public static void main(String[] args) {
		try {
			int count=0;
			ServerSocket serverSocket=new ServerSocket(12345);
			while(true){
				Socket socket=serverSocket.accept();
				new ServerThread(socket).start();
				count++;
				System.out.println("当前连接人数：" + count);
				System.out.println("当前连接客户端的IP:" + socket.getInetAddress().getHostAddress());
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
