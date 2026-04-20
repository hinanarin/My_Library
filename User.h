#pragma once

#include<iostream>

class User
{
public:
	User();
	User(int user_id, const std::string& name, const std::string& password, int user_type);
	virtual ~User();

	bool login(const std::string& input_name, const std::string& input_password);// 登录验证（核心功能）

	
	int get_user_id() const;
	std::string get_user_name() const;
	std::string get_password() const;
	int get_user_type() const;

	
	void set_name(const std::string& new_name);
	void set_password(const std::string& new_password);

	void show_info() const;
	bool change_password();

protected:
	int user_id_;
	std::string user_name_;
	std::string password_;
	int user_type_;// 1=学生  2=管理员

};