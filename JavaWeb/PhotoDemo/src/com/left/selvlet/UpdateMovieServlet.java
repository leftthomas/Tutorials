package com.left.selvlet;

import com.left.service.MovieService;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * 更新一条数据
 * 
 * @author left
 * 
 */
@SuppressWarnings("serial")
public class UpdateMovieServlet extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// 解决中文乱码问题
		request.setCharacterEncoding("UTF-8");
		MovieService movieService = new MovieService();
		List<String> movie=new ArrayList<String>();
		String id = request.getParameter("upid");
		String title = request.getParameter("uptitle");
		String description = request.getParameter("updescription");
		movie.add(id);
		movie.add(title);
		movie.add(/*fileName*/"");
		movie.add(description);
		movieService.updateMovie(movie);;
		request.getRequestDispatcher("/servlet/MovieServlet").forward(request,
				response);

	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);

	}

}
