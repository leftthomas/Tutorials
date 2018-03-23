package com.left.selvlet;

import com.left.bean.Movie;
import com.left.service.MovieService;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

/**
 * Servlet负责与jsp页面进行交互，数据传输 接收客户端发送过来的用户请求，控制不同请求交付给不同事务处理
 * 
 * @author left
 * 
 */
@SuppressWarnings("serial")
public class MovieServlet extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// 解决中文乱码问题
		request.setCharacterEncoding("UTF-8");
		MovieService movieService = new MovieService();
		List<Movie> movies = movieService.queryMovieList();
		String title = request.getParameter("title");
		if (title != null && !"".equals(title.trim())) {
			movies.clear();
			movies.add(movieService.findMovie(title));
		}
		// 向网页传数据，重点是这个函数！！
		request.setAttribute("movielist", movies);
		request.getRequestDispatcher("/WEB-INF/jsp/list.jsp").forward(request,
				response);

	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);

	}

}
