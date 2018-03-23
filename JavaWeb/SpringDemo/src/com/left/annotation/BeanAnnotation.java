package com.left.annotation;

import org.springframework.stereotype.Component;
/*
 * 默认注解没有写beanname的话就是类名首字母小写，其他一致
 * 默认scope是singleton
 */
@Component
public class BeanAnnotation {

	public void sya(String agr){
		System.out.println("BeanAnnotation:"+agr);
	}
}
