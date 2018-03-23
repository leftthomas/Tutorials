package com.left.chain;

import java.util.Random;

/**
 * 责任链模式测试
 * 解耦，仅仅依赖于所提供的接口，依赖于抽象而非具体
 * @author left
 *
 */
public class Test {

	public static void main(String[] args) {
		Customer customer=new Customer();
		customer.setPriceHandler(PriceHandlerFactory.createPriceHandler());
		Random rand=new Random();
		for(int i=0;i<100;i++){
			System.out.print(i+":");
			customer.requestDiscount(rand.nextFloat());
		}
	}

}
