package com.left.proxy;
/**
 * 继承的方式实现静态代理
 * @author left
 *
 */
public class Car2 extends Car {
	@Override
	public void move() {
		long starttime=System.currentTimeMillis();
        System.out.println("汽车开始行驶");
        super.move();
		long endtime=System.currentTimeMillis();
        System.out.println("汽车结束行驶");
        System.out.println("行驶时间：" + (endtime - starttime) + "ms");
    }
}
