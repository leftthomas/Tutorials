package com.left.db;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.Reader;

/**
 * 访问数据库类
 * @author left
 *
 */
public class DBAccess {
	public SqlSession getSqlSession() throws IOException{
		Reader reader=Resources.getResourceAsReader("com/left/configure/Configuration.xml");
		SqlSessionFactory sqlSessionFactory=new SqlSessionFactoryBuilder().build(reader);
		SqlSession sqlSession=sqlSessionFactory.openSession();
		return sqlSession;
	}
}
