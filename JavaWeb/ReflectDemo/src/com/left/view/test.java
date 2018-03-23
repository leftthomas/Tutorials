package com.left.view;

import com.left.achieve.Usage;
/**
 * 反射机制的运用，动态加载类
 * @author left
 *
 */
public class test {

	public static void main(String[] args) {
		try {
			Class c=Class.forName("com.left.function.Jump");
			Usage u=(Usage)c.newInstance();
			u.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Class c=Class.forName("com.left.function.Walk");
			Usage u=(Usage)c.newInstance();
			u.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Class c=Class.forName("com.left.function.Run");
			Usage u=(Usage)c.newInstance();
			u.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
