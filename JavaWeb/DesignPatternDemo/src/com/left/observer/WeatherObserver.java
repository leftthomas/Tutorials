package com.left.observer;

import java.util.Observable;
import java.util.Observer;
/**
 * 实现了java.util包里的接口
 * 具体地观察者对象
 * @author left
 *
 */
public class WeatherObserver implements Observer {

	private String observerName;
	public void update(Observable o, Object arg) {
        //推方式
        System.out.println(observerName + "推送:" + arg);
        //拉方式
        System.out.println(observerName + "拉出:" + ((WeatherSubject) o).getContent());
    }
	public String getObserverName() {
		return observerName;
	}
	public void setObserverName(String observerName) {
		this.observerName = observerName;
	}

}
