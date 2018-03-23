package com.left.udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class Server {
	public static void main(String[] args) {
		try {
			DatagramSocket socket = new DatagramSocket(8800);
			byte[] data = new byte[1024];
			DatagramPacket packet = new DatagramPacket(data, data.length);
			socket.receive(packet);
			String info = new String(data, 0, packet.getLength());
			System.out.println("服务器端接收到的数据：" + info);

			//响应客户端请求
			InetAddress address=packet.getAddress();
			int port=packet.getPort();
			byte[] data2="welcome".getBytes();
			DatagramPacket packet2=new DatagramPacket(data2, data2.length, address, port);
			socket.send(packet2);
			socket.close();
		} catch (SocketException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
}
