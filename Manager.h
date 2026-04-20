#pragma once
#include<string>
#include<iostream>
#include"User.h"
#include"Book.h"
#include"BorrowRecord.h"
#include<vector>
#include<string>

class Manager : public User
{
    public:
    Manager();
    Manager(int user_id,const std::string& user_name,const std::string& password);
    ~Manager() override;

    void handle_manager_menu(std::vector<Book>&all_books,std::vector<BorrowRecord>& borrow_records);

    //管理员功能
    void add_book(std::vector<Book>&all_books);
    void delete_book(std::vector<Book>&all_books);
    void show_all_borrow_records(const std::vector <BorrowRecord>& borrow_records) const;
    static bool attempt_login(const std::vector<Manager>&managers,Manager& logged_in_manager);
    void search_books(const std::vector<Book>& all_books) const;
private:
    void show_manager_menu() const;
    
};

