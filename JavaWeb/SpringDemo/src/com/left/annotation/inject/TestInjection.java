package com.left.annotation.inject;

import com.left.UnitTestBase;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.BlockJUnit4ClassRunner;
/**
 * 注解实现
 * @author mmfq2
 *
 */
@RunWith(BlockJUnit4ClassRunner.class)
public class TestInjection extends UnitTestBase{

	public TestInjection() {
		super("classpath:spring-beanannotation.xml");
	}
	
	@Test
	public void testSetter(){
        //注意bean名字，没有显式声明，则是首字母小写
        InjectionService service=super.getBean("injectionServiceImpl");
	    service.InjectionServicesay("hahaha");
	}

}