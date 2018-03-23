package com.left.inject;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.BlockJUnit4ClassRunner;

import com.left.UnitTestBase;

@RunWith(BlockJUnit4ClassRunner.class)
public class TestInjection extends UnitTestBase{

	public TestInjection() {
		super("classpath:spring-injection.xml");
	}
	
	@Test
	public void testSetter(){
		InjectionService service=super.getBean("injectionService");
		service.InjectionServicesay("hahahha");
	}
	
	@Test
	public void testLife(){
		InjectionDao dao=super.getBean("injectionDao");
	}
}

/*System.out.println("We are single");
		Person you = new Person();
		if (you.getProfession().equals("Front end Engineer")
				|| you.getProfession().equals("Senior Java Engineer")) {
			System.out.println("Come with us!");
			if(you.getStatus().equals("single")){
				System.out.println("It's better!");
			}
		}*/