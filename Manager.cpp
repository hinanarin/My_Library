#include<iostream>
#include<string>
#include"Manager.h"
#include<iostream>

Manager::Manager() : User(){}
Manager::Manager(int user_id,const std::string& user_name,const std::string& password):User(user_id,user_name,password,2)
{}
Manager::~Manager() {}

void Manager::show_manager_menu()const
{
    std::cout << "\n=== 管理员菜单 (" << get_user_name() << ") ===\n";
    std::cout << "1. 查看所有图书\n";
    std::cout << "2. 添加新图书\n";
    std::cout << "3. 删除图书\n";
    std::cout << "4. 查看所有借阅记录\n";
    std::cout << "5. 返回主菜单\n";
    std::cout << "=================\n";
}

void Manager::handle_manager_menu(std::vector<Book>& all_books, 
                                 std::vector<BorrowRecord>& borrow_records)
{
    while (true) {
        std::cout << "\n=== 管理员菜单 (" << get_user_name() << ") ===\n";
        std::cout << "1. 查看所有图书\n";
        std::cout << "2. 搜索图书\n";
        std::cout << "3. 添加新图书\n";
        std::cout << "4. 删除图书\n";
        std::cout << "5. 查看所有借阅记录\n";
        std::cout << "6. 查看个人信息\n";
        std::cout << "7. 修改密码\n";
        std::cout << "8. 返回主菜单\n";
        std::cout << "=================\n";

        int choice;
        std::cout << "请输入您的选择：";
        std::cin >> choice;

        if (choice == 8) break;

        switch (choice)
        {
        case 1:
            for (const auto& book : all_books) {
                book.display_info();
            }
            break;
        case 2:
            search_books(all_books);
            break;
        case 3:
            add_book(all_books);
            break;
        case 4:
            delete_book(all_books);
            break;
        case 5:
            show_all_borrow_records(borrow_records);
            break;
        case 6:
            show_info();
            break;
        case 7:
            change_password();
            break;
        default:
            std::cout << "输入错误！请重新选择。\n";
        }
    }
}

void Manager::add_book(std::vector<Book>& all_books)
{
    int id,total;
    std::string name,author,isbn;
    std::cout << "请输入图书ID: ";
    std::cin >> id;
    std::cout << "请输入书名: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "请输入作者: ";
    std::getline(std::cin, author);
    std::cout << "请输入ISBN: ";
    std::cin >> isbn;
    std::cout << "请输入库存数量: ";
    std::cin >> total;
    all_books.emplace_back(id,name,author,isbn,total);
    std::cout<<"图书添加成功！\n";
}

void Manager::delete_book(std::vector<Book>& all_books)
{
    int id;
    std::cout<<"请输入您要删除的图书ID:";
    std::cin>>id;
    for (auto it = all_books.begin();it != all_books.end();++it)
    {
        if (it->get_book_id()==id)
        {
            std::cout<<"已删除:《"<<it->get_book_name()<<"》\n";
            all_books.erase(it);
            return;
        }
    }
    std::cout<<"未找到该图书!\n";
}

void Manager::show_all_borrow_records(const std::vector<BorrowRecord>& borrow_records) const
{
    std::cout << "\n=== 所有借阅记录 ===\n";
    if (borrow_records.empty()) {
        std::cout << "目前没有借阅记录。\n";
        return;
    }
    for (const auto& r : borrow_records) {
        r.display();
    }
}

bool Manager::attempt_login(const std::vector<Manager>& managers, Manager& logged_in_manager)
{
    std::string username, password;
    std::cout << "\n=== 管理员登录 ===\n";
    std::cout << "请输入管理员用户名: ";
    std::cin >> username;
    std::cout << "请输入密码: ";
    std::cin >> password;

    std::cout << "【调试】输入用户名: " << username << " | 输入密码: " << password << "\n";  // 调试用

    for (const auto& mgr : managers) {
        std::cout << "【调试】比对用户: " << mgr.get_user_name() << "\n";   // 调试用

        if (mgr.get_user_name() == username) {
            Manager temp = mgr;
            if (temp.login(username, password)) {
                logged_in_manager = temp;
                std::cout << "✅ 管理员登录成功！欢迎，" << username << "！\n";
                return true;
            } else {
                std::cout << "【调试】密码验证失败\n";
            }
        }
    }

    std::cout << "❌ 用户名或密码错误！\n";
    return false;
}

void Manager::search_books(const std::vector<Book>& all_books) const
{
    // 可以直接调用 Student 的逻辑，或者复制一份，这里为了简单直接复制
    if (all_books.empty()) {
        std::cout << "当前没有图书。\n";
        return;
    }

    std::string keyword;
    std::cout << "\n请输入搜索关键词（书名或作者）: ";
    std::cin.ignore();
    std::getline(std::cin, keyword);

    std::cout << "\n=== 搜索结果 ===\n";
    bool found = false;

    for (const auto& book : all_books) {
        if (book.get_book_name().find(keyword) != std::string::npos ||
            book.get_author().find(keyword) != std::string::npos) {
            book.display_info();
            found = true;
            }
    }

    if (!found) {
        std::cout << "未找到包含 \"" << keyword << "\" 的图书。\n";
    }
}


























