#include"Book.h"
#include<string>
#include<iostream>


Book::Book()
	: book_id_(0), book_name_(""), author_(""), isbn_(""),
	total_count_(0), available_count_(0)
{
}

Book::Book(int book_id, const std::string& book_name, const std::string& author, const std::string& isbn, int total_count)
	: book_id_(book_id), book_name_(book_name), author_(author), isbn_(isbn), 
	total_count_(total_count), available_count_(total_count){ }

Book::~Book()
{ }

bool Book::borrow_one()
{
	if (available_count_ > 0)
	{
		--available_count_;
		std::cout << "借书成功！《" << book_name_ << "》\n";
		return true;
	}
	else
	{
		std::cout << "借书失败！《" << book_name_ << "》没有库存了。\n";
		return false;
	}
}

bool Book::return_one()
{
	if (available_count_ < total_count_)
	{
		++available_count_;
		std::cout << "还书成功！《" << book_name_ << "》\n";
		return true;
	}
	else
	{
		std::cout << "还书失败！《" << book_name_ << "》的库存已满，无法再归还了。\n";
		return false;
	}
}

bool Book::is_available()const
{
	return available_count_ > 0;
}

// Getter 实现
int Book::get_book_id()const{return book_id_;}
std::string Book::get_book_name()const { return book_name_; }
std::string Book::get_author()const { return author_; }
std::string Book::get_isbn()const { return isbn_; }
int Book::get_total_count()const { return total_count_; }
int Book::get_available_count()const { return available_count_; }

void Book::display_info()const
{
	std::cout << "-----------------------------------\n";
	std::cout << "图书ID: " << book_id_ << "\n";
	std::cout << "书名: " << book_name_ << "\n";
	std::cout << "作者: " << author_ << "\n";
	std::cout << "ISBN: " << isbn_ << "\n";
	std::cout << "总库存: " << total_count_
		<< " | 当前可借: " << available_count_ << "\n";
	std::cout << "-----------------------------------\n";
}

void Book::set_available_count(int count)
{
	if (count > 0 && count <= total_count_)
	{
		available_count_ = count;
	}
}