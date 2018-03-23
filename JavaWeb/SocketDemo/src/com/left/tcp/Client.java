package com.left.tcp;

import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * 客户端
 * @author left
 *
 */
public class Client {
	public static void main(String[] args) {
		try {
			Socket socket=new Socket("localhost", 12345);
			//客户端向服务器端发送数据
			OutputStream stream=socket.getOutputStream();
			PrintWriter writer=new PrintWriter(stream);
			writer.write("用户名：left;密码：123");
			writer.flush();
			socket.shutdownOutput();
			//接收服务器端发送回来的信息
			InputStream inputStream=socket.getInputStream();
			InputStreamReader reader=new InputStreamReader(inputStream);
			BufferedReader bufferedReader=new BufferedReader(reader);
			String data=bufferedReader.readLine();
			//循环读取数据，输出的是服务器端发送过来的数据
			while(data!=null){
				System.out.println(data);
				data=bufferedReader.readLine();
			}
			//关闭资源
			bufferedReader.close();
			reader.close();
			inputStream.close();
			writer.close();
			stream.close();
			socket.close();
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}	
}
