package com.left.annotation;

import com.left.UnitTestBase;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.BlockJUnit4ClassRunner;
/**
 * 注解bean的使用
 * @author left
 *
 */
@RunWith(BlockJUnit4ClassRunner.class)
public class TestAnnotation extends UnitTestBase{

	public TestAnnotation() {
		super("classpath:spring-beanannotation.xml");
	}
	
	
	@Test
	public void TestAnno(){
		BeanAnnotation beanAnnotation=super.getBean("beanAnnotation");
		beanAnnotation.sya("aaaa");
	}
	
}