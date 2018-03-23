package com.left.servlet;

import com.left.bean.User;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class LoginServlet extends HttpServlet {

	public LoginServlet() {
		super();
	}

	public void destroy() {
		super.destroy();
	}

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doPost(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
        response.setCharacterEncoding("utf-8");
        request.setCharacterEncoding("utf-8");
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		User user = new User();
		user.setUsername(username);
		user.setPassword(password);
        System.out.println("操作成功" + user.getUsername() + ","
                + user.getPassword());
        // 保存到session中
        request.getSession().setAttribute("user", user);
        // 跳转到登录成功页面,网址不变
        //request.getRequestDispatcher("/loginsuccess.jsp").forward(request,
			//	response);
        //重定向，网址改变
        response.sendRedirect("../loginsuccess.jsp");
	}

	public void init() throws ServletException {
	}

}
