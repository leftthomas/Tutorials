package com.left.selvlet;

import com.left.service.MovieService;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * 删除单条数据Servlet
 * 
 * @author left
 * 
 */
@SuppressWarnings("serial")
public class DeleteMovieServlet extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// 解决中文乱码问题
		request.setCharacterEncoding("UTF-8");
		MovieService movieService = new MovieService();
		String id = request.getParameter("id");
		movieService.deleteMovie(id);
		request.getRequestDispatcher("/servlet/MovieServlet").forward(request,
				response);

	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);

	}

}
