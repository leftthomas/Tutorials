package com.left.resource;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.BlockJUnit4ClassRunner;

import com.left.UnitTestBase;

@RunWith(BlockJUnit4ClassRunner.class)
public class TestResource extends UnitTestBase{

	public TestResource() {
		super("classpath:spring-resource.xml");
	}
	
	@Test
	public void testResource(){
		LeftResource leftResource=super.getBean("LeftResource");
		leftResource.resource();
	}
	
}