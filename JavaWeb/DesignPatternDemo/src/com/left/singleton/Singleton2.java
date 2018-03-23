package com.left.singleton;

/**
 * 单例模式 在整个应用程序中仅有一份实例 
 * 分为饿汉式、懒汉式两种
 * 这里为懒汉式
 * 线程不安全
 * @author left
 * 
 */
public class Singleton2 {
	// 仅这里声明一份实例
	private static Singleton2 instance;

	// 将构造方法私有化，不允许外部直接创建
	private Singleton2() {
	}

	// 外部通过这个方法来获取实例
	public static Singleton2 getInstance() {
		//只有调用了才生成实例
		if(instance==null){
			instance=new Singleton2();
		}	
		return instance;
	}
}
