#pragma once

#include<string>

class Book
{
public:
	Book();
	Book(int book_id, const std::string& book_name, const std::string& author, const std::string& isbn, int total_count);
	~Book();
	// 核心操作
	bool borrow_one();// 借出一本
	bool return_one();// 归还一本
	bool is_available()const;// 是否有库存

	//Getter
	int get_book_id()const;
	std::string get_book_name()const;
	std::string get_author()const;
	std::string get_isbn()const;
	int get_total_count()const;
	int get_available_count()const;

	void display_info()const;// 显示图书信息
	void set_available_count(int count);
	
private:
	int book_id_;// 图书ID
	std::string book_name_;// 书名
	std::string author_;// 作者
	std::string isbn_;// ISBN
	int total_count_;// 总库存
	int available_count_;// 当前可借数量

};



