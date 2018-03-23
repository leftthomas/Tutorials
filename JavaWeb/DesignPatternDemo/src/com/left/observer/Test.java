package com.left.observer;
/**
 * 观察者模式测试，分为拉模型和推模型两种
 * @author left
 *
 */
public class Test {

	public static void main(String[] args) {
		ConcreteSubject subject=new ConcreteSubject();
		ConcreteObserver observerGirl=new ConcreteObserver();
		observerGirl.setObserverName("right");
		ConcreteObserver observerBoy=new ConcreteObserver();
		observerBoy.setObserverName("left");
		subject.attach(observerBoy);
		subject.attach(observerGirl);
		//set完之后自动触发消息发布
		subject.setSubjectState("测试发布消息");
	}
}
