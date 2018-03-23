package com.left.factory;
/**
 * 工厂模式
 * 发型工厂
 * @author left
 *
 */
public class HairFactory {
	public HairInterface getHair(String key){
		if("left".equals(key))
			return new LeftHair();
		else if("right".equals(key))
			return new RightHair();
		else
			return null;
	}

    //利用反射机制,优化getHair(String key)方法，每增加新的发型不需要改写此处代码
    public HairInterface getHairByClass(String className){
		try {
			HairInterface hairInterface=(HairInterface)Class.forName(className).newInstance();
			return hairInterface;
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		}
		return null;
	}
}
