package com.left.annotation.inject;

import org.springframework.stereotype.Repository;


/**
 * Dao层接口的实现类
 * @author left
 *
 */
@Repository
public class InjectionDaoImpl implements InjectionDao{

	@Override
	public void InjectionDaosay(String args) {
        //模拟数据库操作
        System.out.println("InjectionDaosay:"+args);
	}
}
