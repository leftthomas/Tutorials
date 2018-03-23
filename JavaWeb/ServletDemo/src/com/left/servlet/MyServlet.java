package com.left.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class MyServlet extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		System.out.println("doGet");
		PrintWriter writer=resp.getWriter();
		resp.setContentType("text/html; charset=utf-8");
		writer.println("<strong>servlet doget<strong><br>");
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		System.out.println("doPost");
		PrintWriter writer=resp.getWriter();
		resp.setContentType("text/html; charset=utf-8");
		writer.println("<strong>servlet dopost<strong><br>");
	}

}
