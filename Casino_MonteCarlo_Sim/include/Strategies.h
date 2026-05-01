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
        
          // cược = baseBet * 2^losses
        double bet = baseBet * std::pow(2, losses);

        // không được vượt quá vốn
        bet = std::min(bet, balance);

        // chọn 1 cửa cố định (ví dụ: BAU)
        if (bet > 0) {
            bets[Symbol::BAU] = bet;
        }
        
        
        
    
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
        
           // Danh sách tất cả cửa
        std::vector<Symbol> symbols = {
            Symbol::BAU, Symbol::CUA, Symbol::TOM,
            Symbol::CA, Symbol::GA, Symbol::NAI
        };

        // random chọn 3 cửa
        static std::mt19937 rng(std::random_device{}());
        std::shuffle(symbols.begin(), symbols.end(), rng);

        int numBets = 3;

        // tổng cược = 3 * baseBet
        double totalBet = baseBet * numBets;

        // nếu không đủ tiền → scale xuống
        if (totalBet > balance) {
            double adjustedBet = balance / numBets;
            for (int i = 0; i < numBets; ++i) {
                bets[symbols[i]] = adjustedBet;
            }
        } else {
            for (int i = 0; i < numBets; ++i) {
                bets[symbols[i]] = baseBet;
            }
        }
        
        
        
        
        
        return bets;
    }
};
