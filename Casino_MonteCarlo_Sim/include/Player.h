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
    const std::string& getName() const {
        return name;
    }
    double getBalance() const {
        return balance;
    }
    std::map<Symbol, double> getBets() const {
        return strategy->calculateBets(balance, baseBet, consecutiveLosses);
    }
    void updateBalance(double amount) {
        balance += amount;
        if (amount > 0) {
            consecutiveLosses = 0;
        }
        else if (amount < 0) {
            consecutiveLosses++;
        }
        if (balance < 0) {
            balance = 0;
        }
    }
};
