package com.left.dao;

import com.left.bean.Movie;
import com.left.db.DBAccess;
import org.apache.ibatis.session.SqlSession;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * MyBatis使用,具体的数据操作业务逻辑
 * 
 * @author left
 * 
 */
public class MovieDao {
	// 查询所有数据
	public List<Movie> queryMovieList() {
		DBAccess dbAccess = new DBAccess();
		List<Movie> movies = new ArrayList<Movie>();
		SqlSession sqlSession = null;
		try {
			sqlSession = dbAccess.getSqlSession();
			// 通过对接口的调用直接获取结果，避免对配置文件的操作
			IMovie iMovie = sqlSession.getMapper(IMovie.class);
			movies = iMovie.queryMovieList();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (sqlSession != null) {
				sqlSession.close();
			}
		}
		return movies;
	}

	// 查询单条数据
	public Movie findMovie(String title) {
		DBAccess dbAccess = new DBAccess();
		SqlSession sqlSession = null;
		Movie movie = null;
		try {
			sqlSession = dbAccess.getSqlSession();
			IMovie iMovie = sqlSession.getMapper(IMovie.class);
			movie = iMovie.findMovie(title);
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (sqlSession != null) {
				sqlSession.close();
			}
		}
		return movie;
	}

	// 插入单条数据
	public void insertMovie(Movie movie) {
		DBAccess dbAccess = new DBAccess();
		SqlSession sqlSession = null;
		try {
			sqlSession = dbAccess.getSqlSession();
			IMovie iMovie = sqlSession.getMapper(IMovie.class);
			iMovie.insertMovie(movie);
			// MyBatis下需要手动提交，不然不会执行插入操作
			sqlSession.commit();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (sqlSession != null) {
				sqlSession.close();
			}
		}
	}

	// 删除单条数据
	public void deleteMovie(int id) {
		DBAccess dbAccess = new DBAccess();
		SqlSession sqlSession = null;
		try {
			sqlSession = dbAccess.getSqlSession();
			IMovie iMovie = sqlSession.getMapper(IMovie.class);
			iMovie.deleteMovie(id);
			// MyBatis下需要手动提交，不然不会执行删除操作
			sqlSession.commit();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (sqlSession != null) {
				sqlSession.close();
			}
		}
	}

	// 更新单条数据
	public void updateMovie(Movie movie) {
		DBAccess dbAccess = new DBAccess();
		SqlSession sqlSession = null;
		try {
			sqlSession = dbAccess.getSqlSession();
			IMovie iMovie = sqlSession.getMapper(IMovie.class);
			iMovie.updateMovie(movie);
			// MyBatis下需要手动提交，不然不会执行更新操作
			sqlSession.commit();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (sqlSession != null) {
				sqlSession.close();
			}
		}
	}

}
