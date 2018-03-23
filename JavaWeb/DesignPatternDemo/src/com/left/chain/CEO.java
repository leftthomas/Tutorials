package com.left.chain;
/**
 * CEO，可以批准55%以内的折扣
 * 折扣超出55%，就拒绝申请
 * @author left
 *
 */
public class CEO extends PriceHandler{

	@Override
	public void processDiscount(float discount) {
		if(discount<=0.55){
            System.out.format("%s批准了折扣：%.2f%n", this.getClass().getName(), discount);
        }else{
            System.out.format("%s拒绝了折扣：%.2f%n", this.getClass().getName(), discount);
        }
	}

}
