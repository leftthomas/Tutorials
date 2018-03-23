package com.left.view;

import com.left.control.Control;
import com.left.model.User;

import java.util.List;

/**
 * 视图层测试
 * @author left
 *
 */
public class test {

	public static void main(String[] args) throws Exception {
		Control control=new Control();
        //增
        User user=new User();
        user.setName("me");
        control.add(user);
        //查
        System.out.println(control.get(2).getName());
        //删
        control.del(2);
        List<User> users=control.query();
		for (int i = 0; i < users.size(); i++) {
			System.out.println(users.get(i).getId()+","+users.get(i).getName());
		}
        //改
        user.setId(126);
		user.setName("awr");
		control.edit(user);
	}

}
