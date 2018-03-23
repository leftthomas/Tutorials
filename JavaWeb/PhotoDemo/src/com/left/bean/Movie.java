package com.left.bean;

import java.sql.Timestamp;

/**
 * 模型层的数据结构，将数据库数据进行映射
 * @author left
 *
 */
public class Movie {
	private int id;
    private String title;// 图片名称
    private String img_url;// 图片地址
    private String description;// 图片描述
    private Timestamp create_time;// 创建时间
    private Timestamp update_time;// 更新时间
    private int is_delete;// 是否删除

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public String getImg_url() {
		return img_url;
	}

	public void setImg_url(String img_url) {
		this.img_url = img_url;
	}

	public Timestamp getCreate_time() {
		return create_time;
	}

	public void setCreate_time(Timestamp create_time) {
		this.create_time = create_time;
	}

	public Timestamp getUpdate_time() {
		return update_time;
	}

	public void setUpdate_time(Timestamp update_time) {
		this.update_time = update_time;
	}

	public int getIs_delete() {
		return is_delete;
	}

	public void setIs_delete(int is_delete) {
		this.is_delete = is_delete;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

}
