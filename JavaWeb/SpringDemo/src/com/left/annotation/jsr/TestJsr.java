package com.left.annotation.jsr;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.BlockJUnit4ClassRunner;

import com.left.UnitTestBase;

@RunWith(BlockJUnit4ClassRunner.class)
public class TestJsr extends UnitTestBase{

	public TestJsr() {
		super("classpath:spring-beanannotation.xml");
	}
	
	@Test
	public void testJ(){
		JsrServer jsrServer=getBean("jsrServer");
		jsrServer.save();
	}
	
}