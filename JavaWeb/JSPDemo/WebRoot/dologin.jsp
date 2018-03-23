<%@page import="java.net.URLDecoder"%>
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

<title>登录验证</title>

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
	<h1>登录成功</h1>
	<% request.setCharacterEncoding("utf-8");%>
	用户名：<%=request.getParameter("username") %><br>
	密码：<%=request.getParameter("password") %><br>
	<% if("left".equals(request.getParameter("username")) && "123456".equals(request.getParameter("password"))) 
		out.println("登录成功");
	else out.println("登录失败");
	%>
	<br>
	<%
	Cookie[]cc=request.getCookies();
	if(cc!=null && cc.length>0){
		for(int i=0;i<cc.length;i++){
			out.println(cc[i].getName()+","+URLDecoder.decode(cc[i].getValue(), "utf-8"));
		}
	}
	%>
</body>
</html>
