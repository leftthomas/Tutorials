package com.left.inject;

/**
 * 服务层的接口实现类
 * @author left
 *
 */
public class InjectionServiceImpl implements InjectionService{
	
	private InjectionDao injectionDao;

    //设值注入
    public void setInjectionDao(InjectionDao injectionDao) {
		this.injectionDao = injectionDao;
	}

    //构造器注入
    /*public InjectionServiceImpl(InjectionDao injectionDao) {
		this.injectionDao = injectionDao;
	}*/

	@Override
	public void InjectionServicesay(String args) {
        //模拟业务操作
        System.out.println("InjectionServicesay：" + args);
        args+=this.hashCode();
		injectionDao.InjectionDaosay(args);
	}

}
