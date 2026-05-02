#pragma once
#include "BettingStrategy.h"
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>

class ChungThuyStrategy : public BettingStrategy {
public:
    std::map<Symbol, double> calculateBets(double balance, double baseBet, int losses) const override {
        std::map<Symbol, double> bets;
        double amount = baseBet * std::pow(2, losses);
        amount = std::min(amount, balance);

        if (amount > 0) {
            static thread_local std::mt19937 rng(std::random_device{}());
            std::uniform_int_distribution<int> dist(0, 5);

            Symbol randomSymbol = static_cast<Symbol>(dist(rng));
            bets[randomSymbol] = amount;
        }
        return bets;
    }
};

class RaiThamStrategy : public BettingStrategy {
public:
    std::map<Symbol, double> calculateBets(double balance, double baseBet, int losses) const override {
        std::map<Symbol, double> bets;
        double splitBet = std::min(baseBet, balance / 3.0);
        if (splitBet > 0) {
            static thread_local std::mt19937 rng(std::random_device{}());

            std::vector<Symbol> allSymbols = {
                Symbol::BAU, Symbol::CUA, Symbol::TOM,
                Symbol::CA, Symbol::GA, Symbol::NAI
            };

            std::shuffle(allSymbols.begin(), allSymbols.end(), rng);

            bets[allSymbols[0]] = splitBet;
            bets[allSymbols[1]] = splitBet;
            bets[allSymbols[2]] = splitBet;
        }
        return bets;
    }
};
