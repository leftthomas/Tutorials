package com.left.proxy;
/**
 * 使用聚合方式实现代理,推荐使用此种方式
 * @author left
 *
 */
public class CarLogProxy implements Moveable {

	private Moveable moveable;

	public CarLogProxy(Moveable moveable) {
		super();
		this.moveable=moveable;
	}

	public void move() {
        System.out.println("日志开始");
        moveable.move();
        System.out.println("日志结束");

	}

}
