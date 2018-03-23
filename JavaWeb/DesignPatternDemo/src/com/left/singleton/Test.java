package com.left.singleton;
/**
 * 单例模式的测试
 * @author left
 *
 */
public class Test {

	public static void main(String[] args) {
		Singleton s1=Singleton.getInstance();
		Singleton s2=Singleton.getInstance();
		System.out.println(s1.equals(s2));
		
		Singleton2 s3=Singleton2.getInstance();
		Singleton2 s4=Singleton2.getInstance();
		System.out.println(s3.equals(s4));
	}

}
