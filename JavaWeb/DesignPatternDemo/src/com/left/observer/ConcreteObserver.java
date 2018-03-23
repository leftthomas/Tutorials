package com.left.observer;

/**
 * 具体的观察者对象，实现更新的方法，使自身的状态和目标的状态保持一致
 * 
 * @author left
 * 
 */
public class ConcreteObserver implements Observer {

	private String observerName;
    // 观察者的状态
    private String observerState;

	public void update(Subject subject) {
		observerState = ((ConcreteSubject) (subject)).getSubjectState();
		System.out.println(observerName+":"+observerState);
	}

	public String getObserverName() {
		return observerName;
	}

	public void setObserverName(String observerName) {
		this.observerName = observerName;
	}

}
