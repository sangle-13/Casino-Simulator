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
    /*
    
    
    
    */
};