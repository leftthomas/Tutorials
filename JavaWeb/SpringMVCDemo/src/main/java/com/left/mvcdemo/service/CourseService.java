package com.left.mvcdemo.service;

import org.springframework.stereotype.Service;
import com.left.mvcdemo.model.Course;

@Service
public interface CourseService {
	
	Course getCoursebyId(Integer courseId);
}
