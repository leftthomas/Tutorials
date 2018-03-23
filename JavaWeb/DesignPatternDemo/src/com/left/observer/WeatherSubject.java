package com.left.observer;

import java.util.Observable;
/**
 * 利用jdk提供的观察者模式实现来简化
 * 目标具体实现类
 * @author left
 *
 */
public class WeatherSubject extends Observable {
	private String content;

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
        //这句话不能少，因为继承了Observable
        this.setChanged();
        //拉模型实现
        //this.notifyObservers();
        //推模型实现
        this.notifyObservers(content);
	}
	
}
