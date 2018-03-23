package com.left.annotation;

import java.lang.reflect.Method;

public class Test {
	@SuppressWarnings({ "deprecation", "unchecked", "rawtypes" })
	public static void main(String[] args) {
		Person person = new Child();
		person.sing();

		// 解析注解
		try {
			Class c = Class.forName("com.left.annotation.Child");
			boolean isExist = c.isAnnotationPresent(Description.class);
			if (isExist) {
				Description description = (Description) c
						.getAnnotation(Description.class);
				System.out.println(description.desc());

			}
			Method[] methods = c.getMethods();
			for (Method method : methods) {
				boolean ismExist = method
						.isAnnotationPresent(Description.class);
				if (ismExist) {
					Description description = (Description) method
							.getAnnotation(Description.class);
					System.out.println(description.desc());

				}
			}
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
}
