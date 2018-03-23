package com.left.control;

import com.left.dao.UserDao;
import com.left.model.User;

import java.util.List;
/**
 * 控制层封装，向视图层提供接口
 * @author left
 *
 */
public class Control {

	public void add(User user) throws Exception {
		UserDao userDao = new UserDao();
		userDao.addUser(user);
	}

	public void edit(User user) throws Exception {
		UserDao userDao = new UserDao();
		userDao.updateUser(user);;
	}

	public void del(int id) throws Exception {
		UserDao userDao = new UserDao();
		userDao.delUser(id);
	}

	public List<User> query() throws Exception {
		UserDao userDao = new UserDao();
		return userDao.query();
	}

	public User get(int id) throws Exception {
		UserDao userDao = new UserDao();
		return userDao.get(id);
	}

}
