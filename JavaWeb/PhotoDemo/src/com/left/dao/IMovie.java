package com.left.dao;

import com.left.bean.Movie;

import java.util.List;
/**
 * 接口式编程，与配置文件关联起来，避免Dao中直接对配置文件的调用,松耦合
 * @author left
 *
 */
public interface IMovie {
	//删除一部电影，并非真正意义上的删除，只是将is_delete属性置为1
	public void deleteMovie(int id);

	//查询一部电影
	public Movie findMovie(String title);

	//查询所有电影
	public List<Movie> queryMovieList();

	//插入一部电影
	public void insertMovie(Movie movie);

	//更新一部电影
	public void updateMovie(Movie movie);
}
