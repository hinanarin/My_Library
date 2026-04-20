#pragma once
#include<string>
#include<ctime>

class BorrowRecord
{
public:
    BorrowRecord();
    BorrowRecord(int record_id,int user_id,int book_id,const std::string& book_name,const std::string& user_name);
    void display ()const;

    int get_record_id()const;
    int get_user_id()const;
    int get_book_id()const;
    std::string get_book_name()const;
    std::string get_user_name()const;
    std::string get_borrow_date()const;
private:
    int record_id_;
    int user_id_;
    int book_id_;
    std::string book_name_;
    std::string user_name_;
    std::string borrow_date_;
    
    
    
};