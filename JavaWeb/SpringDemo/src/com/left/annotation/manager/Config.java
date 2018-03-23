package com.left.annotation.manager;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.ImportResource;
@Configuration
@ImportResource("classpath:config.xml")
public class Config {
	@Value("${url}")
	private String url;
    //注意，一定要写成非username,不然会与系统用户名冲突
    @Value("${jdbc.username}")
	private String username;
	@Value("${password}")
	private String password;
	
	@Bean
	public MyDriverManager myDriverManager(){
		return new MyDriverManager(url, username, password);
	}
}
