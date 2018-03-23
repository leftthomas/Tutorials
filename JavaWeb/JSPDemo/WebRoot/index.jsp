<%@page import="java.net.URLEncoder"%>
<%@ page language="java" import="java.util.*,com.left.beans.*,javax.servlet.http.*"
	contentType="text/html; charset=utf-8"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://"
			+ request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<base href="<%=basePath%>">

<title>登录</title>
<meta http-equiv="pragma" content="no-cache">
<meta http-equiv="cache-control" content="no-cache">
<meta http-equiv="expires" content="0">
<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
<meta http-equiv="description" content="This is my page">
<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
</head>

<body>
	<h1>JSP Demo</h1>
	<h2>注册登录</h2>
	<form action="dologin.jsp" name="loginForm" method="post">
		<table>
			<tr>
				<td>用户名：</td>
				<td><input type="text" name="username" /></td>
			</tr>
			<tr>
				<td>密码：</td>
				<td><input type="password" name="password" /></td>
			</tr>
			<tr>
				<td>重复密码：</td>
				<td><input type="password" name="repassword" /></td>
			</tr>
			<tr>
				<td colspan="2"><input type="submit" value="登录" /></td>
			</tr>
		</table>
	</form>
	<br>
	<br>
	<a href="dologin.jsp?username=手术费">url传参</a>
	<% User user=new User();
	user.setUsername("left");
	user.setPassword("aa");
	Cookie userCookie=new Cookie("username",URLEncoder.encode("左手", "utf-8"));
	//userCookie.setMaxAge(10);
	Cookie passCookie=new Cookie("password",user.getPassword());
	//passCookie.setMaxAge(10);
	response.addCookie(userCookie);
	response.addCookie(passCookie);
	out.println(user.getUsername()+","+user.getPassword());
	%>
</body>
</html>
