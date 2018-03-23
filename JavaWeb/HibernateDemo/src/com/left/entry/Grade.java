package com.left.entry;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.OneToMany;
import java.util.HashSet;
import java.util.Set;

@Entity
public class Grade {
	@Id
	@GeneratedValue
	private int gid;
	private String gname;
	private String gdesc;
	@OneToMany
    private Set<Student> students = new HashSet();

	public Grade() {
	}

	public Grade(int gid, String gname, String gdesc, Set<Student> students) {
		super();
		this.gid = gid;
		this.gname = gname;
		this.gdesc = gdesc;
		this.students = students;
	}

    public String getGdesc() {
        return gdesc;
    }

    public void setGdesc(String gdesc) {
        this.gdesc = gdesc;
    }

	@Override
	public String toString() {
		return "Grade [gid=" + gid + ", gname=" + gname + ", gdesc=" + gdesc
				+ ", students=" + students + "]";
	}

	public int getGid() {
		return gid;
	}

	public void setGid(int gid) {
		this.gid = gid;
	}

	public String getGname() {
		return gname;
	}

	public void setGname(String gname) {
		this.gname = gname;
	}

	public Set<Student> getStudents() {
		return students;
	}

	public void setStudents(Set<Student> students) {
		this.students = students;
	}
}
