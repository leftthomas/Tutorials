package com.left.selvlet;

import com.left.bean.Movie;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
/**
 * 做跳转到修改页面的参数传递中转
 * @author left
 *
 */
@SuppressWarnings("serial")
public class TransportServlet extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// 解决中文乱码问题
		request.setCharacterEncoding("UTF-8");
		String id = request.getParameter("id");
		String title = request.getParameter("title");
		String img_url = request.getParameter("img_url");
		String description = request.getParameter("description");
		Movie movie = new Movie();
		movie.setId(Integer.valueOf(id));
		movie.setTitle(title);
		movie.setImg_url(img_url);
		movie.setDescription(description);
		// 向网页传数据，重点是这个函数！！
		request.setAttribute("movie", movie);
		request.getRequestDispatcher("/WEB-INF/jsp/update.jsp").forward(request,
				response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);

	}

}
