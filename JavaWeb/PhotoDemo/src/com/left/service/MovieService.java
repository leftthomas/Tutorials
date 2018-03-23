package com.left.service;

import com.left.bean.Movie;
import com.left.dao.MovieDao;

import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

/**
 * 接收Servlet的要求进行事务处理，并做一些简单的数据预处理，交付给Dao层做处理，获得结果后返还给Servlet
 * 
 * @author left
 * 
 */
public class MovieService {
	// 删除一部电影
	public void deleteMovie(String id) {
		// 将获取到的String类型数据进行转换，由Service处理，Servlet不做处理
		if (id != null && !"".equals(id.trim())) {
			MovieDao movieDao = new MovieDao();
			movieDao.deleteMovie(Integer.valueOf(id));
		}
	}

	// 查询一部电影
	public Movie findMovie(String title) {
		MovieDao movieDao = new MovieDao();
		Movie movie = movieDao.findMovie(title);
		return movie;
	}

	// 查询所有电影
	public List<Movie> queryMovieList() {
		MovieDao movieDao = new MovieDao();
		return movieDao.queryMovieList();
	}

	// 插入一部电影
	public void insertMovie(List<String> parameters) {
		MovieDao movieDao = new MovieDao();
		Movie movie = new Movie();
		Date date = new Date();
		String nowTime = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss")
				.format(date);
		// 将时间格式转换成符合Timestamp要求的格式.
		Timestamp create_time = Timestamp.valueOf(nowTime);// 把时间转换
		movie.setCreate_time(create_time);
		movie.setTitle(parameters.get(0));
		movie.setImg_url(parameters.get(1));
		movie.setDescription(parameters.get(2));
		movie.setIs_delete(0);
		Date date2 = new Date();
		String nowTime2 = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss")
				.format(date2);
		Timestamp update_time = Timestamp.valueOf(nowTime2);
		movie.setUpdate_time(update_time);
		movieDao.insertMovie(movie);
	}

	// 更新一部电影
	public void updateMovie(List<String> parameters) {
		// 传进来的movie对象只需要id、title、img_url、description即可
		MovieDao movieDao = new MovieDao();
		Movie movie = new Movie();
		movie.setId(Integer.valueOf(parameters.get(0)));
		movie.setTitle(parameters.get(1));
		movie.setImg_url(parameters.get(2));
		movie.setDescription(parameters.get(3));
		Date date = new Date();// 获得系统时间.
		// 将时间格式转换成符合Timestamp要求的格式.
		String nowTime = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss")
				.format(date);
		Timestamp update_time = Timestamp.valueOf(nowTime);
		movie.setUpdate_time(update_time);
		movieDao.updateMovie(movie);
	}
}
