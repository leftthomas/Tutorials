package com.left.aware;

import org.springframework.beans.BeansException;
import org.springframework.context.ApplicationContext;
import org.springframework.context.ApplicationContextAware;
/**
 * 实现ApplicationContextAware接口来获取LeftApplicationContext所在的配置文件
 * @author left
 *
 */
public class LeftApplicationContext implements ApplicationContextAware{

	private ApplicationContext applicationContext;
	@Override
	public void setApplicationContext(ApplicationContext arg0)
			throws BeansException {
		this.applicationContext=arg0;
		System.out.println("LeftApplicationContext:"+arg0.getBean("LeftApplicationContext").hashCode());
	}
	
	public void a(){
		applicationContext.getBeanDefinitionCount();
	}

}
