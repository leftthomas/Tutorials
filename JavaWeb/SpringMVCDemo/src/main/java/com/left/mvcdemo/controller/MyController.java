package com.left.mvcdemo.controller;
/**
 * 记得配置run config里面的jetty运行时端口，不要用8080，已经被占用了
 * @RequestMapping表示映射到哪个url路径,以项目根路径为基准
 */
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/hello")
public class MyController {
	
	@RequestMapping("/mvc")
	//响应的请求url为host:8083/hello/mvc
	public String helloMvc(){
		return "home";
	}
}
