package com.left.dao;

import com.left.model.User;

import java.util.List;
/**
 * 接口式编程，与配置文件关联起来，避免Dao中直接对配置文件的调用
 * @author left
 *
 */
public interface IUser {
	public List<User> queryUserList();
	public User queryUser(int id);
	public void deleteOne(int id);
	public void insertOne(String name);
	public void deleteBatch(List<Integer> ids);
}
