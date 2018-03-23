<%@ page language="java" import="java.util.*"
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

<title>Servlet Demo</title>
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
<a href="servlet/MyServlet">MY_____Get方式请求Servlet </a>
<form action="servlet/MyServlet" method="post">
<input type="submit" value="MY_____Post方式请求Servlet"/>
</form>
<a href="servlet/TestServlet">TEST_____Get方式请求Servlet </a>
<form action="servlet/TestServlet" method="post">
<input type="submit" value="MY_____Post方式请求Servlet"/>
</form>
<br>
<br>
<form action="servlet/LoginServlet" method="post">
<input type="text" name="username">
<input type="password" name="password">
<input type="submit" value="LoginPost方式请求Servlet"/>
</form>
</body>
</html>
