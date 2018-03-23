package com.left.calculate;

import org.junit.Test;

import static org.junit.Assert.assertEquals;
/**
 * 单元测试类,@Test作注解，测试方法必须是public void，不带参数
 * assert 断言
 * @author left
 *
 */
public class CaculateTest {

	@Test
	public void testAdd(){
		assertEquals(6, new Calculate().add(3, 3));
	}

	@Test
	public void testSub(){
		assertEquals(3, new Calculate().sub(4, 7));
	}
	

	@Test
	public void testMul(){
		assertEquals(9, new Calculate().mul(3, 3));
	}

	@Test
	public void testDiv(){
		assertEquals(0, new Calculate().div(4,0));
	}

    @Test(timeout = 2000)//单位为毫秒
    public void testWhile(){
		while(true){
			System.out.println("left ahhaha");
		}
	}
}
