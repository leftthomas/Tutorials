package com.left.url;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;

/**
 * URL的相关使用
 * @author left
 *
 */
public class MyUrl {
	public static void main(String[] args) {
		try {
			URL main=new URL("http://www.baidu.com");
			URL url=new URL(main, "/index.html?username=left#test");
			System.out.println("主机IP:" + url.getHost());
			//若未指定端口号，返回值为-1
			System.out.println("端口号：" + url.getPort());
			System.out.println("查询条件：" + url.getQuery());
			System.out.println("文件路径：" + url.getFile());
			System.out.println("相对路径:" + url.getRef());
			
			InputStream stream=url.openStream();
			//将字节流转换为字符流，并且指定编码为utf-8
			InputStreamReader reader=new InputStreamReader(stream, "utf-8");
			//添加缓冲流，提高读取速度
			BufferedReader bufferedReader=new BufferedReader(reader);
			String data=bufferedReader.readLine();
			//循环读取网页数据，输出的其实就是html文本
			while(data!=null){
				System.out.println(data);
				data=bufferedReader.readLine();
			}
			bufferedReader.close();
			reader.close();
			stream.close();
		} catch (MalformedURLException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
}
