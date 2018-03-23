package com.left.autowiring;

import com.left.UnitTestBase;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.BlockJUnit4ClassRunner;
/**
 * 自动装配
 * @author left
 *
 */
@RunWith(BlockJUnit4ClassRunner.class)
public class TestAutowiring extends UnitTestBase{

	public TestAutowiring() {
		super("classpath:spring-autowiring.xml");
	}
	
	
	@Test
	public void TestAuto(){
		AutowiringService autowiringService=super.getBean("AutowiringService");
		autowiringService.say("tets");
	}
	
}