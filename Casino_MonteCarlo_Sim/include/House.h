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
    
    // Lấy tên nhà cái
    const std::string& getName() const {
        return name;
    }

    // Vốn hiện tại
    double getBalance() const {
        return balance;
    }

    // Vốn ban đầu
    double getInitialBalance() const {
        return initialBalance;
    }

    // Cập nhật vốn (dương: lời, âm: lỗ)
    void updateBalance(double amount) {
        balance += amount;

        // Nếu muốn chặt chẽ hơn (không cho âm):
        if (balance < 0) {
            balance = 0;
        }
    }

    // Kiểm tra phá sản
    bool isBankrupt() const {
        return balance <= 0;
    }
};
