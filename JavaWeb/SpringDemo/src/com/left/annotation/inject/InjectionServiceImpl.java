package com.left.annotation.inject;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 * 服务层的接口实现类
 * @author left
 *
 */
@Service
public class InjectionServiceImpl implements InjectionService{
	
	@Autowired
	private InjectionDao injectionDao;

	@Override
	public void InjectionServicesay(String args) {
        //模拟业务操作
        System.out.println("InjectionServicesay：" + args);
        args+=this.hashCode();
		injectionDao.InjectionDaosay(args);
	}
}
