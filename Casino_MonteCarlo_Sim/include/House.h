#pragma once
#include <string>

class House {
private:
    std::string name;
    double balance;
    double initialBalance;

public:
    House(const std::string& n, double bal) : name(n), balance(bal), initialBalance(bal) {}
    //Viết hàm getName lấy tên nhà cái
    //Viết hàm getBalance lấy vốn nhà cái hiện tại
    // viết hàm getInitialBalance lấy vốn ban đầu nhà cái
    // viết hàm updateBalance cập nhật số vốn nhà cái
    // viết hàm isBankrupt kiểm tra nhà cái phá sản chưa
    /*
    
    
    
    */
};