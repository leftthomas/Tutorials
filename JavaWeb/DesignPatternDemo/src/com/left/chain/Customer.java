package com.left.chain;
/**
 * 客户，请求折扣
 * @author left
 *
 */
public class Customer {

	private PriceHandler priceHandler;
	public void requestDiscount(float discount){
		priceHandler.processDiscount(discount);
		
	}
	public void setPriceHandler(PriceHandler priceHandler) {
		this.priceHandler = priceHandler;
	}
}
