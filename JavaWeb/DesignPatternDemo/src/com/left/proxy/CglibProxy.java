package com.left.proxy;

import net.sf.cglib.proxy.Enhancer;
import net.sf.cglib.proxy.MethodInterceptor;
import net.sf.cglib.proxy.MethodProxy;

import java.lang.reflect.Method;

/**
 * Cglib动态代理,需要jar包
 * 
 * @author left
 * 
 */
public class CglibProxy implements MethodInterceptor {

	private Enhancer enhancer = new Enhancer();

	@SuppressWarnings("rawtypes")
	public Object getProxy(Class clazz) {
		enhancer.setSuperclass(clazz);
		enhancer.setCallback(this);
		return enhancer.create();
	}

	/**
	 * 拦截所有目标类的方法
	 */
	public Object intercept(Object obj, Method m, Object[] args,
			MethodProxy proxy) throws Throwable {
		System.out.println("hahaha");
		// 代理类调用父类的方法
		proxy.invokeSuper(obj, args);
		return null;
	}
}
