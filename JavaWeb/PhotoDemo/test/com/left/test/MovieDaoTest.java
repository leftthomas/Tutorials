package com.left.test;

import com.left.bean.Movie;
import com.left.dao.MovieDao;
import org.junit.Test;

import java.sql.Timestamp;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import static org.junit.Assert.assertEquals;

/**
 * Dao的业务逻辑单元测试
 * 
 * @author left
 * 
 */
public class MovieDaoTest {

	@Test
	public void testQueryMovieList() {
		MovieDao movieDao = new MovieDao();
		List<Movie> movies = movieDao.queryMovieList();
		assertEquals(7, movies.size());
		for (Movie movie : movies) {
			DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			Date create_date = null, update_time = null;
			Timestamp create_timestamp = movie.getCreate_time();
			Timestamp update_timestamp = movie.getUpdate_time();
			if (create_timestamp != null)
				create_date = new Date(create_timestamp.getTime());
			if (update_timestamp != null)
				update_time = new Date(update_timestamp.getTime());
			String cerateresult = df.format(create_date);
			String updateresult = df.format(update_time);
			System.out.println("电影名：" + movie.getTitle() + "，图片地址："
					+ movie.getImg_url() + "，电影描述：" + movie.getDescription()
					+ "，创建时间：" + cerateresult + "，更新时间：" + updateresult
					+ "，是否删除：" + movie.getIs_delete());
		}

	}

	@Test
	public void testFindMovie() {
		MovieDao movieDao = new MovieDao();
		Movie movie = movieDao.findMovie("灰姑娘");
		assertEquals("灰姑娘", movie.getTitle());
	}

	@Test
	public void testInsertMovie() {
		MovieDao movieDao = new MovieDao();
		Movie movie = new Movie();
		Date date = new Date();//获得系统时间.
		String nowTime = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(date);//将时间格式转换成符合Timestamp要求的格式.
		Timestamp create_time = Timestamp.valueOf(nowTime);//把时间转换
		movie.setCreate_time(create_time);
		movie.setTitle("断线");
		movie.setImg_url("http://img.hb.aicdn.com/6695b570f485437c41f5fe6babba4e84ce2bb513257e2-iIG7VV_fw658");
		movie.setDescription("虚拟的社交网络连了线，真实的人际关系却断了线。聊天室的每句对话、脸书上的一张照片一条短片，背后隐藏着人渴望与人接触的欲望，但却分分钟带来不堪设想的后果。日理万机的大律师无暇与家人相处沟通，直到儿子出事才悔恨爱得太迟；一对婚姻枯燥无味的夫妇各自在网上寻求慰藉，但网络世界何来秘密；孤僻宅男网上会女神，原来一直被玩更误堕色欲陷阱；顽童网上欺凌同学，乐极生悲；女记者为爆独家猛料，故意接近未成年色情网男模，道德界线难划清。几条故事线纠缠交错，每个荡失于虚拟世界的主人翁，只是渴望找到与人真正的联系和沟通。");
		movie.setIs_delete(0);
		Date date2 = new Date();//获得系统时间.
		String nowTime2 = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(date2);//将时间格式转换成符合Timestamp要求的格式.
		Timestamp update_time = Timestamp.valueOf(nowTime2);//把时间转换
		movie.setUpdate_time(update_time);
		movieDao.insertMovie(movie);
		assertEquals(7, movieDao.queryMovieList().size());
	}

	@Test
	public void testDeleteMovie() {
		MovieDao movieDao = new MovieDao();
		movieDao.deleteMovie(2);
		assertEquals(6, movieDao.queryMovieList().size());
	}

	@Test
	public void testUpdateMovie() {
		MovieDao movieDao = new MovieDao();
		Movie movie = new Movie();
		movie.setId(3);
		movie.setTitle("上帝之子");
		movie.setImg_url("http://img.hb.aicdn.com/c69fca9204b85c460cc0d69860ffdfc59e1724d820827-WDevNR_fw658");
		/**
		 * 这里要特别注意，对于数据库中的字段更新，,我之前起的字段名字是desc,不知道为什么更新就是报错，
		 * 会有这个警告：The word 'desc' is not correctly spelled
		 * 后来改成description就没问题了，至于为什么我也不清楚，反正测试结果是这样的
		 * 现在清楚了，这坑爹缩写是数据库的排序保留字！！！！！！
		 */
		movie.setDescription("这是一部英国电影，主演Jeremy Bowen，影片讲述神之子耶稣的生平故事，从他的诞生，传道，受难，到最终的复活，生动地刻画出一个丰满的人物形象[1]  。");
		Date date = new Date();//获得系统时间.
		String nowTime = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(date);//将时间格式转换成符合Timestamp要求的格式.
		Timestamp update_time = Timestamp.valueOf(nowTime);//把时间转换
		movie.setUpdate_time(update_time);
		movieDao.updateMovie(movie);
		assertEquals("上帝之子", movieDao.findMovie("上帝之子").getTitle());
	}
}
