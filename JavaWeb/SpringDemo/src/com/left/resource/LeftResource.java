package com.left.resource;

import org.springframework.beans.BeansException;
import org.springframework.context.ApplicationContext;
import org.springframework.context.ApplicationContextAware;
import org.springframework.core.io.Resource;

import java.io.IOException;

public class LeftResource implements ApplicationContextAware{

	private ApplicationContext applicationContext;
	@Override
	public void setApplicationContext(ApplicationContext arg0)
			throws BeansException {
		this.applicationContext=arg0;
	}
	public void resource() {
        //不写classpath前缀时，默认依赖于applicationContext的创建方式
        Resource resource=applicationContext.getResource("classpath:config.txt");
		try {
			System.out.println(resource.getFilename()+":"+resource.contentLength());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
