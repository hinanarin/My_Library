#include<iostream>
#include<string>
#include<vector>
#include"Student.h"
#include"Book.h"

Student::Student() :User(), max_borrow_limit_(5){}

Student::Student(int user_id, const std::string& user_name, const std::string& user_password) :User(user_id, user_name, user_password,1),
max_borrow_limit_(5)
{

}
Student::~Student()
{

}

void Student::show_all_books(const std::vector<Book>& all_books) const
{
	std::cout << "\n=== 所有图书列表 ===\n" << std::endl;
	if (all_books.empty())
	{
		std::cout<<"目前没见图书\n";
		return;
	}
	for (const auto& book : all_books)
	{
		book.display_info();
	}
}

bool Student::borrow_book(int book_id,std::vector<Book>& all_books,std::vector<BorrowRecord>& borrow_records)
{
	for (auto& book : all_books)
	{
		if(book.get_book_id() == book_id)
			{
				if ( book.borrow_one())
				{
					static int record_counter = 10000;
					BorrowRecord new_record(record_counter++,get_user_id(),book_id,book.get_book_name(),get_user_name());
					borrow_records.push_back(new_record);
					std::cout<<"借阅记录已创建！\n";
					return true;
				}
				return false;
			}
    }
	std::cout << " 未找到ID为 " << book_id << " 的图书！\n";
	return false;
}

bool Student::return_book(int book_id, std::vector<Book>& all_books)
{
	for (auto& book : all_books)
	{
		if (book.get_book_id() == book_id)
		{
			return book.return_one();
			return true;
		}
		std::cout << " 未找到ID为 " << book_id << " 的图书！\n";
		return false;
}
	
}

void Student::show_my_borrowed_records(const std::vector<BorrowRecord>& borrow_records)const
{
	std::cout << "\n=== 我的借阅记录 ===\n" ;
	bool has_record = false;
	for (auto& record : borrow_records)
	{
		if (record.get_user_id() == get_user_id())
		{
			record.display();
			has_record = true;
		}
	}
	if (!has_record)
	{
		std::cout<<"目前没有借阅记录.\n";
	}
}

int Student::get_max_borrow_limit()const
{
	return max_borrow_limit_;
}
void Student::handle_student_menu(std::vector<Book>& all_books, 
								 std::vector<BorrowRecord>& borrow_records)
{
	while (true) {
		std::cout << "\n=== 学生菜单 (" << get_user_name() << ") ===\n";
		std::cout << "1. 查看所有图书\n";
		std::cout << "2. 搜索图书\n";
		std::cout << "3. 借书\n";
		std::cout << "4. 还书\n";
		std::cout << "5. 查看我的借阅记录\n";
		std::cout << "6. 查看个人信息\n";
		std::cout << "7. 修改密码\n";
		std::cout << "8. 返回主菜单\n";
		std::cout << "=================\n";

		int choice;
		std::cout << "请输入您的选择：";
		std::cin >> choice;

		if (choice == 8) {
			std::cout << "返回主菜单...\n";
			break;
		}

		switch (choice)
		{
		case 1:
			show_all_books(all_books);
			break;
		case 2:
			search_books(all_books);
			break;
		case 3: {
				int book_id;
				std::cout << "请输入要借的图书ID: ";
				std::cin >> book_id;
				borrow_book(book_id, all_books, borrow_records);
				break;
		}
		case 4: {
				int book_id;
				std::cout << "请输入要还的图书ID: ";
				std::cin >> book_id;
				return_book(book_id, all_books);
				break;
		}
		case 5:
			show_my_borrowed_records(borrow_records);
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

bool Student::attempt_login(const std::vector<Student>& students,Student& logged_in_student)
{
	std::string username,password;
	std::cout << "\n=== 学生登录 ===\n";
	std::cout << "请输入用户名: ";
	std::cin >> username;
	std::cout << "请输入密码: ";
	std::cin >> password;
	for (const auto& stu : students) {
		// 调用 User 类的 login 方法验证
		if (stu.get_user_name() == username && 
			const_cast<Student&>(stu).login(username, password)) {   // 临时绕过 const
			std::cout << " 登录成功！欢迎回来，" << stu.get_user_name() << "！\n";
			return true;
			}
		std::cout << "用户名或密码错误！登录失败。\n";
		return false;  // 返回空学生（id=0 表示失败）
	}
}

void Student::search_books(const std::vector<Book>& all_books) const
{
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