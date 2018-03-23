package com.left.chain;

public class PriceHandlerFactory {

    //工厂模式,构造责任链关系
    public static PriceHandler createPriceHandler() {
		PriceHandler sales=new Sales();
		PriceHandler lead=new Lead();
		PriceHandler man=new Manager();
		PriceHandler dir=new Director();
		PriceHandler vp=new VicePresident();
		PriceHandler ceo=new CEO();
		sales.setSuccessor(lead);
		lead.setSuccessor(man);
		man.setSuccessor(dir);
		dir.setSuccessor(vp);
		vp.setSuccessor(ceo);
		return sales;
	}

}
