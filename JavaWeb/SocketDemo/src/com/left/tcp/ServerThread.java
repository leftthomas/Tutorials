package com.left.tcp;

import java.io.*;
import java.net.Socket;

/**
 * 服务器端多线程处理类，以解决多用户请求
 * 
 * @author left
 * 
 */
public class ServerThread extends Thread {

	Socket socket;

	public ServerThread(Socket socket) {
		this.socket = socket;
	}

	public void run() {
		InputStream stream = null;
		InputStreamReader reader = null;
		BufferedReader bufferedReader = null;
		OutputStream outputStream = null;
		PrintWriter writer = null;
		try {
			stream = socket.getInputStream();
			reader = new InputStreamReader(stream);
			// 添加缓冲流，提高读取速度
			bufferedReader = new BufferedReader(reader);
			String data = bufferedReader.readLine();
			// 循环读取数据，输出的是客户端发送过来的数据
			while (data != null) {
				System.out.println(data);
				data = bufferedReader.readLine();
			}
			socket.shutdownInput();
			// 响应客户端
			outputStream = socket.getOutputStream();
			writer = new PrintWriter(outputStream);
			writer.write("成功登录！");
			writer.flush();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {

			try {
				// 关闭资源
				writer.close();
				outputStream.close();
				bufferedReader.close();
				reader.close();
				stream.close();
				socket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

}
