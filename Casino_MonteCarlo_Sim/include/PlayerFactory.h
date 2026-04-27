#pragma once
#include "Player.h"
#include "Strategies.h"
#include <memory>
#include <string>

class PlayerFactory {
public:
    enum class Type { CHUNG_THUY, RAI_THAM };

    static std::unique_ptr<Player> createPlayer(Type type, const std::string& name, double balance) {
        double defaultBaseBet = 100.0;
        std::unique_ptr<BettingStrategy> strat;

        switch (type) {
        case Type::CHUNG_THUY:
            strat = std::make_unique<ChungThuyStrategy>(); break;
        case Type::RAI_THAM:
            strat = std::make_unique<RaiThamStrategy>(); break;
        }
        return std::make_unique<Player>(name, balance, defaultBaseBet, std::move(strat));
    }
};