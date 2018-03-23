package com.left.aware;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.BlockJUnit4ClassRunner;

import com.left.UnitTestBase;

@RunWith(BlockJUnit4ClassRunner.class)
public class TestAware extends UnitTestBase{

	public TestAware() {
		super("classpath:spring-aware.xml");
	}
	
	@Test
	public void TestApplicationContext(){
		System.out.println("TestApplicationContext:"+super.getBean("LeftApplicationContext").hashCode());
	}
	
	@Test
	public void TestBeanName(){
		System.out.println("TestBeanName:"+super.getBean("LeftBeanName"));
	}
	
}