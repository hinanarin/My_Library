#include "Student.h"   // 先包含具体的类定义
#include "Manager.h"
#include "FileUtil.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <vector>
#include <string>
#include <charconv> // 新增：用于高效数字转换

namespace fs = std::filesystem;

// --- 内部辅助工具：把一行字符串按分隔符切开 ---
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void FileUtil::ensure_data_directory() {
    if (!fs::exists("data")) {
        fs::create_directory("data");
    }
}

// --- 图书存取 ---
bool FileUtil::save_books(const std::vector<Book>& books, const std::string& filename) {
    ensure_data_directory();
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto& b : books) {
        // 统一格式：ID|书名|作者|ISBN|总数|可用数
        file << b.get_book_id() << "|" << b.get_book_name() << "|"
             << b.get_author() << "|" << b.get_isbn() << "|"
             << b.get_total_count() << "|" << b.get_available_count() << "\n";
    }
    return true;
}

bool FileUtil::load_books(std::vector<Book>& books, const std::string& filename) {
    books.clear();
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        auto t = split(line, '|');
        if (t.size() < 6) continue; // 跳过格式不全的行
        try {
            Book book(std::stoi(t[0]), t[1], t[2], t[3], std::stoi(t[4]));
            book.set_available_count(std::stoi(t[5]));
            books.push_back(book);
        } catch (...) { continue; } // 即使stoi失败也不崩溃，直接跳过
    }
    return true;
}

// --- 用户存取 (学生和管理员) ---
bool FileUtil::save_users(std::vector<Student>& students, std::vector<Manager>& managers, const std::string& filename) {
    ensure_data_directory();
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto& s : students) 
        file << "1|" << s.get_user_id() << "|" << s.get_user_name() << "|" << s.get_password() << "\n";
    for (const auto& m : managers) 
        file << "2|" << m.get_user_id() << "|" << m.get_user_name() << "|" << m.get_password() << "\n";
    
    return true;
}

bool FileUtil::load_users(std::vector<Student>& students, std::vector<Manager>& managers, const std::string& filename) {
    students.clear(); managers.clear();
    std::ifstream file(filename, std::ios::binary); // 以二进制模式打开，防止系统自动转换换行符
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        // 1. 清理行尾（同时处理 \n 和 \r）
        line.erase(line.find_last_not_of("\r\n") + 1);
        if (line.empty()) continue;

        auto t = split(line, '|');
        if (t.size() < 4) continue;

        // 2. 健壮的数字转换（自动跳过 BOM 头或非数字前缀）
        auto safe_to_int = [](std::string_view sv) {
            int val = 0;
            auto first = sv.data();
            auto last = sv.data() + sv.size();
            // 跳过任何非数字字符（比如文件开头的 BOM）
            while (first < last && !std::isdigit(static_cast<unsigned char>(*first))) first++;
            std::from_chars(first, last, val);
            return val;
        };

        // 3. 提取数据
        int type = safe_to_int(t[0]);
        int id   = safe_to_int(t[1]);
        std::string name = t[2];
        std::string pwd  = t[3];

        if (type == 1) students.emplace_back(id, name, pwd);
        else if (type == 2) managers.emplace_back(id, name, pwd);
    }
    return true;
}

// --- 借阅记录存取 ---
bool FileUtil::save_borrow_records(const std::vector<BorrowRecord>& records, const std::string& filename) {
    ensure_data_directory();
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    for (const auto& r : records) {
        file << r.get_record_id() << "|" << r.get_user_id() << "|" << r.get_book_id() << "|"
             << r.get_book_name() << "|" << r.get_user_name() << "|" << r.get_borrow_date() << "\n";
    }
    return true;
}

bool FileUtil::load_borrow_records(std::vector<BorrowRecord>& records, const std::string& filename) {
    records.clear();
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string line;
    while (std::getline(file, line)) {
        auto t = split(line, '|');
        if (t.size() < 6) continue;
        try {
            records.emplace_back(std::stoi(t[0]), std::stoi(t[1]), std::stoi(t[2]), t[3], t[4]);
        } catch (...) { continue; }
    }
    return true;
}



















