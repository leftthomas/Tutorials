package com.left.singleton;

/**
 * 单例模式 在整个应用程序中仅有一份实例 
 * 分为饿汉式、懒汉式两种
 * 这里为饿汉式
 * 线程安全
 * @author left
 * 
 */
public class Singleton {
	// 仅这里生成一份实例
	private static Singleton instance = new Singleton();

	// 将构造方法私有化，不允许外部直接创建
	private Singleton() {
	}

	// 外部通过这个方法来获取实例
	public static Singleton getInstance() {
		return instance;
	}

}
