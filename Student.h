#pragma once

#include<iostream>
#include<string>
#include"User.h"
#include<vector>
#include"Book.h"
#include "BorrowRecord.h"
#include"FileUtil.h"

class Student : public User
{
public:
	Student();
	Student(int user_id, const std::string& name, const std::string& password);
	~Student()override;

	//学生专属功能
	void handle_student_menu(std::vector<Book>& all_books,std::vector<BorrowRecord>& borrow_records);
	void show_all_books(const std::vector<Book>& all_books) const;// 查看所有图书
	bool borrow_book(int book_id, std::vector<Book>& all_books,std::vector<BorrowRecord>& borrow_records) ;// 借书
	bool return_book(int book_id,std::vector<Book>& all_books);// 还书
	void show_my_borrowed_records(const std::vector<BorrowRecord>& borrow_records) const;// 查看我的借阅记录
	static bool attempt_login(const std::vector<Student>& students,Student& logged_in_student);
	// C++17 特性示例：使用 [[nodiscard]] 提醒调用者不要忽略返回值
	[[nodiscard]] int get_max_borrow_limit() const;// 学生最多能借几本书
	void search_books(const std::vector<Book>& all_books) const;
private:
	int max_borrow_limit_ = 5; // 学生的最大借书数量限制

};


























