package com.left.aware;

import org.springframework.beans.factory.BeanNameAware;

public class LeftBeanName implements BeanNameAware{

	@Override
	public void setBeanName(String arg0) {
		System.out.println("LeftBeanName:"+arg0);
	}

}
