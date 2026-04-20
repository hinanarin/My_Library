#define _CRT_SECURE_NO_WARNINGS
#include"BorrowRecord.h"
#include<string>
#include<iostream>
#include<ctime>
#include<iomanip>
#include<sstream>

BorrowRecord::BorrowRecord()
    :record_id_(0),user_id_(0),book_id_(0),book_name_(""),user_name_(""),borrow_date_("")
{}

BorrowRecord::BorrowRecord(int record_id,int user_id,int book_id,const std::string& book_name,const std::string& user_name)
    :record_id_(record_id),
    user_id_(user_id),
    book_id_(book_id),
    book_name_(book_name),
    user_name_(user_name)
{
    // 获取当前时间作为借书日期
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    std::ostringstream oss;
    oss<<(local_time -> tm_year+1900)<<"-"
    <<std::setw(2)<<std::setfill('0')<<(local_time -> tm_mon+1)<<"-"
    <<std::setw(2)<<std::setfill('0')<<local_time ->tm_mday;
    borrow_date_ = oss.str();
}

void BorrowRecord::display () const
{
    std::cout << "借阅记录ID: " << record_id_ 
              << " | 图书: " << book_name_
              << " | 借书人: " << user_name_
              << " | 借书日期: " << borrow_date_ << "\n";
}

int BorrowRecord::get_record_id() const {return record_id_;}
int BorrowRecord::get_user_id() const { return user_id_; }
int BorrowRecord::get_book_id() const { return book_id_; }
std::string BorrowRecord::get_book_name() const { return book_name_; }
std::string BorrowRecord::get_user_name() const { return user_name_; }
std::string BorrowRecord::get_borrow_date() const { return borrow_date_; }









































