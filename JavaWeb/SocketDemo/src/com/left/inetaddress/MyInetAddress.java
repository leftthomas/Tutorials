package com.left.inetaddress;

import java.net.InetAddress;
import java.net.UnknownHostException;


/**
 * 获取IP地址相关信息
 * @author left
 *
 */
public class MyInetAddress {
	public static void main(String[] args) throws UnknownHostException {
		InetAddress address=InetAddress.getLocalHost();
		System.out.println("本计算机名：" + address.getHostName());
		System.out.println("本机IP：" + address.getHostAddress());
		
		InetAddress address2=InetAddress.getByName("192.168.1.100");
		System.out.println("指定IP的计算机名：" + address2.getHostName());
	}
}
