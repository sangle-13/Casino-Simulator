#pragma once
#include <string>
#include <memory>
#include <map>
#include "BettingStrategy.h"

class Player {
private:
    std::string name;
    double balance;
    double baseBet;
    int consecutiveLosses = 0;
    std::unique_ptr<BettingStrategy> strategy;

public:
    Player(const std::string& n, double bal, double bBet, std::unique_ptr<BettingStrategy> strat)
        : name(n), balance(bal), baseBet(bBet), strategy(std::move(strat)) {
    }
    //viết hàm getName (lấy tên người chơi) getBalance (lấy số vốn hiện tại)
    //Viết hàm getBets trả về 1 std::map (của cược, số tiền) người chơi sẽ đánh trong ván kế tiếp
    // viết hàm updateBalance để update vốn người chơi
// Lấy tên người chơi
//
    const std::string& getName() const {
        return name;
    }

    // Lấy số vốn hiện tại
    double getBalance() const {
        return balance;
    }

    // Lấy cược cho ván tiếp theo
    std::map<Symbol, double> getBets() const {
        return strategy->calculateBets(balance, baseBet, consecutiveLosses);
    }

    // Cập nhật vốn người chơi
    void updateBalance(double amount) {
        balance += amount;

        // Nếu thắng → reset chuỗi thua
        if (amount > 0) {
            consecutiveLosses = 0;
        }
        // Nếu thua → tăng chuỗi thua
        else if (amount < 0) {
            consecutiveLosses++;
        }

        // Không cho âm (tránh bug)
        if (balance < 0) {
            balance = 0;
        }
    }
//
};
