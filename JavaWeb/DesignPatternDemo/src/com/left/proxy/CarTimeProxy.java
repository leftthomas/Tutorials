package com.left.proxy;
/**
 * 使用聚合方式实现代理,推荐使用此种方式
 * @author left
 *
 */
public class CarTimeProxy implements Moveable {

	private Moveable moveable;

	public CarTimeProxy(Moveable moveable) {
		super();
		this.moveable=moveable;
	}

	public void move() {
		long starttime = System.currentTimeMillis();
        System.out.println("汽车开始行驶");
        moveable.move();
		long endtime = System.currentTimeMillis();
        System.out.println("汽车结束行驶");
        System.out.println("行驶时间：" + (endtime - starttime) + "ms");

	}

}
