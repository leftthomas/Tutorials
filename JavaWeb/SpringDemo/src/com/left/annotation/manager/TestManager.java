package com.left.annotation.manager;

import com.left.UnitTestBase;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.BlockJUnit4ClassRunner;
/**
 * 配置文件注解实现
 * @author mmfq2
 *
 */
@RunWith(BlockJUnit4ClassRunner.class)
public class TestManager extends UnitTestBase{

	public TestManager() {
		super("classpath:spring-beanannotation.xml");
	}
	
	@Test
	public void testManage(){
		MyDriverManager driverManager=super.getBean("myDriverManager");
		System.out.println(driverManager.getClass().getName());
	}

}