package com.left.entry;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import org.hibernate.cfg.Configuration;
import org.hibernate.service.ServiceRegistry;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

public class StudentTest {

	private SessionFactory factory;
	private Session session;
	private Transaction transaction;

	@Before
	public void init() {
		Configuration configuration = new Configuration().configure();
		ServiceRegistry registry = new StandardServiceRegistryBuilder().applySettings(
				configuration.getProperties()).build();
		factory=configuration.buildSessionFactory(registry);
		session=factory.openSession();
		transaction=session.beginTransaction();
	}

	@After
	public void destory() {
		transaction.commit();
		session.close();
		factory.close();
	}

	@Test
	public void testSaveStudent() throws IOException {
		/*Student student=new Student(1,"right","女","浙江杭州", 1, null);
		File f=new File("d:"+File.separator+"1.jpg");
		InputStream inputStream=new FileInputStream(f);
		Blob image=Hibernate.getLobCreator(session).createBlob(inputStream, inputStream.available());
		student.setPicture(image);
		session.save(student);
		Student student2=(Student) session.get(Student.class,1);
		System.out.println(student2);
		Student student3=(Student) session.load(Student.class,3);
		System.out.println(student3);
		session.delete(student3);
		session.update(student);*/
		Set<Student> set = new HashSet();
		Grade grade = new Grade(1, "三班", "测试", set);
		session.save(grade);
		for(int i=1;i<=10;i++){
			Student student = new Student(1, "right" + i, "女", "浙江杭州", 1, null);
			session.save(student);
			set.add(student);
		}
		grade.setStudents(set);
		session.save(grade);
	}
}
