package com.left.observer;

public class WeatherTest {

	public static void main(String[] args) {
		WeatherSubject subject=new WeatherSubject();
        subject.setContent("今天天气炎热");
        WeatherObserver observer=new WeatherObserver();
		observer.setObserverName("left");
		
		WeatherObserver observer1=new WeatherObserver();
		observer1.setObserverName("right");
		
		subject.addObserver(observer);
		subject.addObserver(observer1);
		
		observer.update(subject, subject.getContent());
		observer1.update(subject, subject.getContent());
		
	}

}
