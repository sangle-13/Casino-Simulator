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
        //viết logic cho chiến thuật chung thủy (mỗi lần thua cược x2 số tiền)
        //đầu vào blance ( vốn hiện có) baseBet(tiền cược cố định) loses (số ván đã thua)
        // đầu ra 1 std::map với cửa cược và tiền cược.
        /*
        
        
        
        
        */
        return bets;
    }
};

class RaiThamStrategy : public BettingStrategy {
public:
    std::map<Symbol, double> calculateBets(double balance, double baseBet, int losses) const override {
        std::map<Symbol, double> bets;
        //viết logic cho chiến thuật rải thảm 
        // đầu vào tương tự chiến thuật chung thủy
        // đầu ra 1 std::map với 3 cặp, mỗi cặp gồm cửa cược và số tiền cược.
        /*
        
        
        
        
        
        */
        return bets;
    }
};