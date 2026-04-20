#pragma once
#include<string>
#include<vector>
#include"Book.h"
#include"BorrowRecord.h"
class Student;
class Manager;
class FileUtil
{
public:
    // 保存和加载图书
    static bool save_books(const std::vector<Book>&books,const std::string& filename="data/book.txt");
    static bool load_books(std::vector<Book>&books,const std::string& filename = "data/book.txt");
    //保存何加载借阅数据
    static bool save_borrow_records(const std::vector<BorrowRecord>&records,const std::string& filename = "data/borrow.txt");
    static bool load_borrow_records(std::vector<BorrowRecord>&records,const std::string& filename = "data/borrow.txt");
    //用户数据相关
    static bool save_users( std::vector<Student>& students,
         std::vector<Manager>& managers,
        const std::string& filename ="data/user.txt");
    static bool load_users(std::vector<Student>& students ,
        std::vector<Manager>& managers,
        const std::string& filename ="data/user.txt");
    // 辅助函数：确保 data 文件夹存在
    static void ensure_data_directory();
};
