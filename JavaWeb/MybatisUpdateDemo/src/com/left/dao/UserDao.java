package com.left.dao;

import com.left.db.DBAccess;
import com.left.model.User;
import org.apache.ibatis.session.SqlSession;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * MyBatis使用
 * 
 * @author left
 * 
 */
public class UserDao {
	public static void main(String[] args) {
		/*
		 * UserDao userDao=new UserDao(); List<User> users=new
		 * ArrayList<User>(); users=userDao.queryUserList(); for (User user :
		 * users) { System.out.println("id:"+user.getId());
		 * System.out.println("name:"+user.getName()); }
		 */

		/*
		 * User user = new User(); user = userDao.queryUser(125);
		 * System.out.println("id:" + user.getId()); System.out.println("name:"
		 * + user.getName());
		 */

		/*
		 * UserDao userDao = new UserDao(); userDao.deleteOne(125); List<User>
		 * users = new ArrayList<User>(); users = userDao.queryUserList(); for
		 * (User usera : users) { System.out.println("id:" + usera.getId());
		 * System.out.println("name:" + usera.getName()); }
		 */

		/*
		 * UserDao userDao = new UserDao(); List<Integer> IDs = new
		 * ArrayList<Integer>(); IDs.add(124); IDs.add(126); IDs.add(129);
		 * userDao.deleteBatch(IDs); List<User> users = new ArrayList<User>();
		 * users = userDao.queryUserList(); for (User usera : users) {
		 * System.out.println("id:" + usera.getId()); System.out.println("name:"
		 * + usera.getName()); }
		 */

		/*
		 * UserDao userDao = new UserDao(); userDao.insertOne("left");
		 */

	}

	// 查询所有用户数据
	public List<User> queryUserList() {
		DBAccess dbAccess = new DBAccess();
		List<User> users = new ArrayList<User>();
		SqlSession sqlSession = null;
		try {
			sqlSession = dbAccess.getSqlSession();
			// users = sqlSession.selectList("User.queryUserList");
			// 通过对接口的调用直接获取结果，避免对配置文件的操作
			IUser iUser = sqlSession.getMapper(IUser.class);
			users = iUser.queryUserList();
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
			// user = sqlSession.selectOne("User.queryUser", id);
			IUser iUser = sqlSession.getMapper(IUser.class);
			user = iUser.queryUser(id);
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
			IUser iUser = sqlSession.getMapper(IUser.class);
			iUser.insertOne(name);
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
			// sqlSession.delete("User.deleteOne", id);
			IUser iUser = sqlSession.getMapper(IUser.class);
			iUser.deleteOne(id);
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

	// 批量删除用户数据
	public void deleteBatch(List<Integer> usersID) {
		DBAccess dbAccess = new DBAccess();
		SqlSession sqlSession = null;
		try {
			sqlSession = dbAccess.getSqlSession();
			// sqlSession.delete("User.deleteBatch", usersID);
			IUser iUser = sqlSession.getMapper(IUser.class);
			iUser.deleteBatch(usersID);
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
}
