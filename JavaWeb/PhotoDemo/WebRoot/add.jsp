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

<title>添加电影页面</title>

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
	<form action="<%=basePath%>servlet/AddServlet" method="get">
		<div style="width: 100%;height: 50px; font-size: 20px;">
			电影名：<input type="text" value="" name="addtitle"
				style="width: 90%;height: 50px;">
		</div>
		<div
			style="width: 100%;height: 150px; font-size: 20px; margin-top: 20px;">
			电影描述：
			<textarea rows="7" cols="1" name="adddescription"
				style="width: 85%;height: 150px;font-size: 15px;"></textarea>
		</div>
		<div
			style="width: 200px;height: 50px; font-size: 20px; margin-top: 20px">
			<input type="file" name="addimg_url"
				style="margin-left:500px;  width: 400px; height: 100px;font-size: 20px;">
		</div>
		<div
			style="width: 200px;height: 50px; font-size: 20px; margin-top: 20px">
			<input type="submit" value="确定"
				style="margin-left:500px;margin-top:100px;  width: 400px; height: 100px;font-size: 20px;">
		</div>
	</form>
</body>
</html>
