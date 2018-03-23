package com.left.udp;

import java.io.IOException;
import java.net.*;

public class Client {

	public static void main(String[] args) {
		try {
			InetAddress address=InetAddress.getByName("localhost");
			int port=8800;
			byte[] data="hello left".getBytes();
			DatagramPacket packet=new DatagramPacket(data, data.length, address, port);
			DatagramSocket socket=new DatagramSocket();
			socket.send(packet);

			//接收服务器端响应的数据
			byte[] data2=new byte[1024];
			DatagramPacket packet2=new DatagramPacket(data2, data2.length);
			socket.receive(packet2);
			String recive=new String(data2, 0, packet2.getLength());
			System.out.println("接收到的服务器端返回的数据：" + recive);
			socket.close();
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (SocketException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
