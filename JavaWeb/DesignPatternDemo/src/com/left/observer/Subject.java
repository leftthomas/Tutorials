package com.left.observer;

import java.util.ArrayList;
import java.util.List;

/**
 * 目标对象，，保存观察者对象，提供注册(添加)和删除观察者的接口
 * @author left
 *
 */
public class Subject {
	private List<Observer> observers=new ArrayList<Observer>();
	public void attach(Observer observer){
		observers.add(observer);
	}
	public void detach(Observer observer){
		observers.remove(observer);
	}
	
	protected void notifyObservers(){
		for (Observer observer : observers) {
			observer.update(this);
		}
	}
}
