#pragma once
#include <map>

enum class Symbol { BAU, CUA, TOM, CA, GA, NAI };

class BettingStrategy {
public:
    virtual ~BettingStrategy() = default;
    virtual std::map<Symbol, double> calculateBets(double balance, double baseBet, int losses) const = 0;
};
//đối tượng thuần ảo mô tả chiến thuật, sẽ được overide trong class con straegies.h
//đã hoàn thành, không code file này.