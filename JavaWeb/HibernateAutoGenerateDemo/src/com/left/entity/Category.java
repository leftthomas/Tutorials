package com.left.entity;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;
import org.hibernate.annotations.GenericGenerator;

/**
 * Category entity. @author MyEclipse Persistence Tools
 */
@Entity
@Table(name = "category", catalog = "left")
public class Category implements java.io.Serializable {

	// Fields

	private Integer id;
	private String catname;
	private String catdescription;

	// Constructors

	/** default constructor */
	public Category() {
	}

	/** minimal constructor */
	public Category(String catname) {
		this.catname = catname;
	}

	/** full constructor */
	public Category(String catname, String catdescription) {
		this.catname = catname;
		this.catdescription = catdescription;
	}

	// Property accessors
	@GenericGenerator(name = "generator", strategy = "increment")
	@Id
	@GeneratedValue(generator = "generator")
	@Column(name = "id", unique = true, nullable = false)
	public Integer getId() {
		return this.id;
	}

	public void setId(Integer id) {
		this.id = id;
	}

	@Column(name = "catname", nullable = false, length = 50)
	public String getCatname() {
		return this.catname;
	}

	public void setCatname(String catname) {
		this.catname = catname;
	}

	@Column(name = "catdescription", length = 200)
	public String getCatdescription() {
		return this.catdescription;
	}

	public void setCatdescription(String catdescription) {
		this.catdescription = catdescription;
	}

}