package com.left.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
/**
 * 构建数据库的连接
 * @author left
 *
 */
public class DBUtil {

	public static Connection conn = null;
	static {
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		try {
			conn = DriverManager.getConnection(
                    "jdbc:mysql://127.0.0.1:3306/left", "root", "password");
        } catch (SQLException e) {
			e.printStackTrace();
		}
	}

	public static Connection getConnection() {
		return conn;
	}
}
