package com.left.factory;
/**
 * 工厂模式的测试
 * @author left
 *
 */
public class Test {

	public static void main(String[] args) {
		HairFactory factory=new HairFactory();
		//HairInterface hairInterface=factory.getHair("left");
		//hairInterface.draw();
		factory.getHairByClass("com.left.factory.LeftHair").draw();
		
	}

}
