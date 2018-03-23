package com.left.test;

import com.left.entity.Student;
import com.left.util.HibernateSessionFactory;
import org.hibernate.Session;

public class Test {

	public static void main(String[] args) {
        Student student = new Student("浙江杭州", "女", 1, null, "left");
        HibernateSessionFactory.getSession().save(student);
		Session session=HibernateSessionFactory.getSession();
		Student student2=(Student) session.get(Student.class, 1);
		System.out.println(student2.getAddress()+student2.getGender()+student2.getSname());
		session.close();
	}

}
