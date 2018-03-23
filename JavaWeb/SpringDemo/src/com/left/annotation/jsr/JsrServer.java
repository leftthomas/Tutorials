package com.left.annotation.jsr;
/**
 * @Resource实现的作用与@Autowired自动装配基本一致,jsr330之后引入@Inject也可实现，不过需要引入javax.inject包
 */
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

@Service
public class JsrServer {
    //直接使用@Resource便可以将此实例注入到当前实例中去
    @Resource
	//@Inject
	private JsrDAO jsrDAO;
	public void save(){
		jsrDAO.save();
	}
}
