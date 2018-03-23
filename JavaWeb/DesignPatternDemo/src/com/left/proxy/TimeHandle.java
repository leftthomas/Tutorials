package com.left.proxy;
/**
 * JDK动态代理
 */
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;

public class TimeHandle implements InvocationHandler {

	private Object target;

	public TimeHandle(Object target) {
		super();
		this.target = target;
	}

	/**
	 * proxy 被代理对象
	 * method 被代理方法
	 * args 方法的参数
	 */
	public Object invoke(Object proxy, Method method, Object[] args)
			throws Throwable {
		long starttime = System.currentTimeMillis();
		System.out.println("汽车开始行驶");
		method.invoke(target);
		long endtime = System.currentTimeMillis();
		System.out.println("汽车结束行驶");
		System.out.println("行驶时间：" + (endtime - starttime) + "ms");
		return null;
	}

}
