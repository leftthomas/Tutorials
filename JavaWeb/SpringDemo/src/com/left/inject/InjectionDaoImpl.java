package com.left.inject;


/**
 * Dao层接口的实现类
 * @author left
 *
 */
public class InjectionDaoImpl implements InjectionDao{

	@Override
	public void InjectionDaosay(String args) {
        //模拟数据库操作
        System.out.println("InjectionDaosay:"+args);
	}
	
	public void stop() {
		System.out.println("bean stop");
	}
	
	public void start(){
		System.out.println("bean start");
	}

}
