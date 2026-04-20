#include<iostream>
#include<string>
#include"User.h"

User::User() :user_id_(0), user_name_(""), password_(""), user_type_(0)
{
	//默认构造函数
}
User::User(int user_id, const std::string& name, const std::string& password, int user_type)
	:user_id_(user_id), user_name_(name), password_(password), user_type_(user_type)
{
	//带参数的构造函数
}
User::~User() {// 暂时为空，后面讲RAII时会加点东西}
}

bool User::login(const std::string & input_name, const std::string & input_password)
	{
		if (input_name == user_name_ && input_password == password_)
		{
			std::cout << "登录成功！欢迎回来," << user_name_ << "！\n";
			return true;
		}
		else
		{
			std::cout << "登录失败！用户名或密码错误，请重试." << std::endl;
			return false;
		}
	}
int User::get_user_id() const
{ 
	return user_id_;
}

std::string User::get_user_name() const
{
	return user_name_;
}

std::string User::get_password() const 
{ 
	return password_; 
}

int User::get_user_type() const
{
	return user_type_;
}

void User::set_name(const std::string& new_name)
{
	user_name_ = new_name;
}

void User::set_password(const std::string& new_password)
{
	password_ = new_password;
}

void User::show_info() const
{
	std::cout << "\n=== 个人信息 ===\n";
	std::cout << "用户ID   : " << user_id_ << "\n";
	std::cout << "用户名   : " << user_name_ << "\n";
	std::cout << "用户类型 : " << (user_type_ == 1 ? "学生" : "管理员") << "\n";
	std::cout << "================\n";
}

bool User::change_password()
{
	std::string old_pwd, new_pwd, confirm_pwd;
	std::cout << "\n=== 修改密码 ===\n";
	std::cout << "请输入当前密码: ";
	std::cin >> old_pwd;

	if (old_pwd != password_) {
		std::cout << "当前密码错误！\n";
		return false;
	}

	std::cout << "请输入新密码: ";
	std::cin >> new_pwd;
	std::cout << "请再次确认新密码: ";
	std::cin >> confirm_pwd;

	if (new_pwd != confirm_pwd) {
		std::cout << "两次输入的新密码不一致！\n";
		return false;
	}

	if (new_pwd.length() < 4) {
		std::cout << "新密码长度不能少于4位！\n";
		return false;
	}

	password_ = new_pwd;
	std::cout << "密码修改成功！\n";
	return true;
}