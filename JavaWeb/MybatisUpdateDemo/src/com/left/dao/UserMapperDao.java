package com.left.dao;

import com.left.db.DBAccess;
import com.left.model.User;
import org.apache.ibatis.session.SqlSession;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * 使用注解的方式，使用方式与XML的类似，省去编写xml的步骤，更加简洁
 * 
 * @author left
 * 
 */
public class UserMapperDao {

	public static void main(String[] args) {

		/*
		 * UserMapperDao userDao = new UserMapperDao(); List<User> users = new
		 * ArrayList<User>(); users = userDao.queryUserList(); for (User user :
		 * users) { System.out.println("id:" + user.getId());
		 * System.out.println("name:" + user.getName()); }
		 */
		UserMapperDao userDao = new UserMapperDao();
		User user = new User();
		user = userDao.queryUser(131);
		System.out.println("id:" + user.getId());
		System.out.println("name:" + user.getName());

		/*
		 * userDao.deleteOne(135); List<User> users = new ArrayList<User>();
		 * users = userDao.queryUserList(); for (User usera : users) {
		 * System.out.println("id:" + usera.getId()); System.out.println("name:"
		 * + usera.getName()); }
		 */

		userDao.insertOne("left333");


	}

	// 查询所有用户数据
	public List<User> queryUserList() {
		DBAccess dbAccess = new DBAccess();
		List<User> users = new ArrayList<User>();
		SqlSession sqlSession = null;
		try {
			sqlSession = dbAccess.getSqlSession();
			UserMapperI iUser = sqlSession.getMapper(UserMapperI.class);
			users = iUser.getAll();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (sqlSession != null) {
				sqlSession.close();
			}
		}
		return users;
	}

	// 查询单条用户数据
	public User queryUser(int id) {
		DBAccess dbAccess = new DBAccess();
		SqlSession sqlSession = null;
		User user = null;
		try {
			sqlSession = dbAccess.getSqlSession();
			UserMapperI iUser = sqlSession.getMapper(UserMapperI.class);
			user = iUser.getById(id);
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (sqlSession != null) {
				sqlSession.close();
			}
		}
		return user;
	}

	// 插入单条用户数据
	public void insertOne(String name) {
		DBAccess dbAccess = new DBAccess();
		SqlSession sqlSession = null;
		try {
			sqlSession = dbAccess.getSqlSession();
			UserMapperI iUser = sqlSession.getMapper(UserMapperI.class);
			User user = new User();
			user.setName(name);
			iUser.add(user);
			// MyBatis下需要手动提交，不然不会执行删除操作
			sqlSession.commit();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (sqlSession != null) {
				sqlSession.close();
			}
		}
	}

	// 删除单条用户数据
	public void deleteOne(int id) {
		DBAccess dbAccess = new DBAccess();
		SqlSession sqlSession = null;
		try {
			sqlSession = dbAccess.getSqlSession();
			UserMapperI iUser = sqlSession.getMapper(UserMapperI.class);
			iUser.deleteById(id);
			sqlSession.commit();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (sqlSession != null) {
				sqlSession.close();
			}
		}
	}
}
