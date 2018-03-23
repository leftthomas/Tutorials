package com.left.servlet;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
/**
 * 控制层核心，接收请求，调用底层接口，处理事务，控制页面跳转
 * @author left
 *
 */
@SuppressWarnings("serial")
public class TestServlet extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doPost(request,response);
	}
	
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//页面跳转
		request.getRequestDispatcher("../test.jsp").forward(request, response);
	}

}
