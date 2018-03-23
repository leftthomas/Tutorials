package com.left.proxy;


/**
 * 代理测试
 * 
 * @author left
 * 
 */
public class Test {
	public static void main(String[] args) {
		/*
		 * Car car = new Car(); car.move(); Car2 car2=new Car2(); car2.move();
		 */
		// Moveable car=new Car2();
		// car.move();
		/*
		 * Car car=new Car(); CarLogProxy logProxy=new CarLogProxy(car);
		 * CarTimeProxy timeProxy=new CarTimeProxy(logProxy); timeProxy.move();
		 */
		/*Car car = new Car();
		InvocationHandler handler = new TimeHandle(car);
		Class<?> cls = car.getClass();
		Moveable moveable = (Moveable) Proxy.newProxyInstance(
				cls.getClassLoader(), cls.getInterfaces(), handler);
		moveable.move();*/
		CglibProxy proxy=new CglibProxy();
		Car car=(Car) proxy.getProxy(Car.class);
		car.move();

	}
}
