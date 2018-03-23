<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://"
			+ request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<meta http-equiv="X-UA-Compatible" content="IE=9; IE=8; IE=7; IE=EDGE" />
<title>电影列表页面</title>
<link href="<%=basePath%>resources/css/all.css" rel="stylesheet"
	type="text/css" />
</head>
<body style="background: #e1e9eb;">
	<form action="<%=basePath%>servlet/MovieServlet" id="mainForm"
		method="post">
		<div class="right">
			<div class="rightCont">
				<p class="g_title fix">
					电影列表 <a class="btn03" href="<%=path%>/add.jsp">新 增</a>&nbsp;&nbsp;&nbsp;&nbsp;
				</p>
				<table class="tab1">
					<tbody>
						<tr>
							<td width="90" align="right">电影名称：</td>
							<td><input type="text" class="allInput" value=""
								name="title" /></td>
							<td width="85" align="right"><input type="submit"
								class="tabSub" value="查 询" /></td>
						</tr>
					</tbody>
				</table>
				<div class="fix">
					<table class="tab2" width="100%">
						<tbody>
							<tr>
								<th width="50">序号</th>
								<th width="100">电影名</th>
								<th>描述</th>
								<th width="50">操作</th>
							</tr>
							<c:forEach items="${movielist}" var="movie" varStatus="status">
								<tr>
									<td width="50">${status.index+1}</td>
									<td width="100">${movie.title}</td>
									<td><img src="<%=path %>/${movie.img_url}"
										style="margin-left: 300px; margin-bottom: 20px; display: block; width: 350px; height: 500px;">${movie.description}</td>
									<td width="100"><a
										href="${basePath}TransportServlet?id=${movie.id}&title=${movie.title}&img_url=${movie.img_url}&description=${movie.description}">修改</a>&nbsp;&nbsp;&nbsp;
										<a href="${basePath}DeleteMovieServlet?id=${movie.id}">删除</a></td>
								</tr>
							</c:forEach>
						</tbody>
					</table>
				</div>
			</div>
		</div>
	</form>
</body>
</html>