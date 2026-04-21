#include<iostream>
#include<string>
#include<vector>
#include"User.h"
#include"Student.h"
#include"Book.h"
#include"BorrowRecord.h"
#include"FileUtil.h"
#include"Manager.h"


void show_main_menu();


void show_main_menu()
{
    std::cout << "\n=== 主菜单 ===\n";
    std::cout << "1. 学生登录\n";
    std::cout << "2. 管理员登录\n";
    std::cout << "3. 退出系统\n";
    std::cout << "===============\n";
}

int main()
{
    // 强制控制台输出和输入都使用 UTF-8 (代码页 65001)
    // 强制控制台输入输出使用 UTF-8

    std::vector<Book> all_books;
    std::vector<BorrowRecord> borrow_records;
    std::vector<Student> students;
    std::vector<Manager> managers;
    std::cout << "========================================\n";
    std::cout << "   欢迎来到 【我的图书馆管理系统】 v1.0\n";
    std::cout << "========================================\n\n";
    FileUtil::ensure_data_directory();
    FileUtil::load_books(all_books, "data/books.txt");
    FileUtil::load_borrow_records(borrow_records, "data/borrow.txt");
   
    FileUtil::load_users(students, managers, "data/users.txt");
   
    if (all_books.empty())
    {
        all_books={
            Book(1001, "C++ Primer", "Stanley Lippman", "978-7-302-12345-6", 5),
            Book(1002, "Effective C++", "Scott Meyers", "978-7-302-54321-0", 3),
            Book(1003, "代码大全", "Steve McConnell", "978-7-302-98765-4", 4),
            Book(1004, "计算机程序的构造和解释", "Harold Abelson", "978-7-302-11111-1", 2)
        };
    }
    std::cout << " 数据加载完成！共有 " << all_books.size() << " 本图书。\n\n";
    
    while (true) {
        show_main_menu();
        int choice;
        std::cout << "请输入您的选择：";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
                // 准备学生列表（后面会从文件加载）
                Student current_student;
                if (Student::attempt_login(students, current_student)) {
                    current_student.handle_student_menu(all_books, borrow_records);
                }
            break;
        }
        case 2:
        {
                Manager current_manager;
                if (Manager::attempt_login(managers, current_manager)) {
                    current_manager.handle_manager_menu(all_books, borrow_records);
                }
                break;
        }
        case 3:
            // 退出前保存所有数据
            FileUtil::save_books(all_books);
            FileUtil::save_borrow_records(borrow_records);
            FileUtil::save_users(students, managers);
            std::cout << "所有数据已保存，感谢使用，再见！👋\n";
            return 0;
        default:
            std::cout << "输入错误！请重新输入。\n";
        }
    }
    
    return 0;
}


