package com.left.autowiring;

public class AutowiringService {
    //名字必须与xml中的id一致
    private AutowiringDao autowiringDao;
	public void setAutowiringDao(AutowiringDao autowiringDao) {
		this.autowiringDao = autowiringDao;
	}
	public void say(String name){
		this.autowiringDao.say(name);
	}
}
