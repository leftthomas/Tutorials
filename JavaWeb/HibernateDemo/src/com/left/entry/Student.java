package com.left.entry;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import java.sql.Blob;

/**
 * 学生类
 * 
 * @author left
 * 
 */
@Entity
public class Student {
	@Id
	@GeneratedValue
	private int sid;
	private String sname;
	private String gender;
	private String address;
	private int gid;
    private Blob picture;


	public Student(int sid, String sname, String gender, String address,
			int gid, Blob picture) {
		this.sid = sid;
		this.sname = sname;
		this.gender = gender;
		this.address = address;
		this.gid = gid;
		this.picture = picture;
	}


    public Student() {

    }

	@Override
	public String toString() {
		return "Student [sid=" + sid + ", sname=" + sname + ", gender="
				+ gender + ", address=" + address + ", gid=" + gid
				+ ", picture=" + picture + "]";
	}

	public int getSid() {
		return sid;
	}

	public void setSid(int sid) {
		this.sid = sid;
	}

	public String getSname() {
		return sname;
	}

	public void setSname(String sname) {
		this.sname = sname;
	}

	public String getGender() {
		return gender;
	}

	public void setGender(String gender) {
		this.gender = gender;
	}


	public String getAddress() {
		return address;
	}

	public void setAddress(String address) {
		this.address = address;
	}

	public Blob getPicture() {
		return picture;
	}

	public void setPicture(Blob picture) {
		this.picture = picture;
	}


	public int getGid() {
		return gid;
	}


	public void setGid(int gid) {
		this.gid = gid;
	}

}
