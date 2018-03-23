package com.left.dao;

import com.left.model.User;
import com.left.util.DBUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
/**
 * 基础的数据库增删查改操作，向控制层提供封装服务
 * @author left
 *
 */
public class UserDao {
	public void addUser(User user) throws Exception {
		Connection conn = DBUtil.getConnection();
		String sql = "insert into user (name) values(?)";
		PreparedStatement prps = conn.prepareStatement(sql);
		prps.setString(1, user.getName());
		prps.execute();
	}

	public void delUser(int id) throws Exception {
		Connection conn = DBUtil.getConnection();
		String sql = "delete from user where id=?";
		PreparedStatement prps = conn.prepareStatement(sql);
		prps.setInt(1, id);
		prps.execute();
	}

	public void updateUser(User user) throws Exception {
		Connection conn = DBUtil.getConnection();
		String sql = "update user set name=? where id=?";
		PreparedStatement prps = conn.prepareStatement(sql);
		prps.setString(1, user.getName());
		prps.setInt(2, user.getId());
		prps.execute();
	}

	public List<User> query() throws Exception {
		Connection conn = DBUtil.getConnection();
		Statement st = conn.createStatement();
		ResultSet sa = st.executeQuery("select name,id from user");
		List<User> users = new ArrayList<User>();

		while (sa.next()) {
			User user = new User();
			user.setId(sa.getInt("id"));
			user.setName(sa.getString("name"));
			users.add(user);
		}
		return users;

	}

	public User get(int id) throws Exception {
		Connection conn = DBUtil.getConnection();
		String sql = "select * from user where id=?";
		PreparedStatement prps = conn.prepareStatement(sql);
		prps.setInt(1, id);
		ResultSet sa = prps.executeQuery();
		User user = null;
		while (sa.next()) {
			user = new User();
			user.setId(sa.getInt("id"));
			user.setName(sa.getString("name"));
		}
		return user;
	}
}
