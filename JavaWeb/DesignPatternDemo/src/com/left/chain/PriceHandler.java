package com.left.chain;
/**
 * 价格处理人，负责处理客户折扣申请
 * @author left
 *
 */
public abstract class PriceHandler {
    //直接后继，用于传递请求
    protected PriceHandler successor;

    //处理折扣申请
    public abstract void processDiscount(float discount);

	/**
	 * @param successor the successor to set
	 */
	public void setSuccessor(PriceHandler successor) {
		this.successor = successor;
	}
	
}
