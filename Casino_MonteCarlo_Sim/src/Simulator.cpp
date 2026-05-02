#include "Simulator.h"
#include <fstream>
#include <iostream>
#include <random>
#include <map>
#include <sstream>

void Simulator::addPlayer(std::unique_ptr<Player> p) {
    players.push_back(std::move(p));
}

void Simulator::run() {
    std::string fullPath = "data/" + outputFileName;
    std::ofstream outFile(fullPath);

    if (!outFile.is_open()) return;

    outFile << "Van";
    for (const auto& p : players) outFile << ",Von_" << p->getName();
    outFile << ",Von_" << house->getName() << "\n";

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 5);

    std::ostringstream buffer;

    for (int i = 1; i <= numSimulations; ++i) {
        std::map<Symbol, int> diceCounts;
        for (int d = 0; d < 3; ++d) {
            Symbol result = static_cast<Symbol>(dist(rng));
            diceCounts[result]++;
        }
        bool allPlayersBankrupt = true;
        buffer << i;

        for (auto& p : players) {
            if (p->getBalance() > 0) {
                allPlayersBankrupt = false;
                auto bets = p->getBets();
                double netChange = 0;

                for (const auto& [sym, amount] : bets) {
                    if (diceCounts.count(sym) > 0) {
                        double winAmount = amount * diceCounts[sym];
                        if (house->getBalance() < winAmount) {
                            winAmount = house->getBalance();
                        }
                        netChange += winAmount;
                        house->updateBalance(-winAmount);
                    }
                    else {
                        netChange -= amount;
                        house->updateBalance(amount);
                    }
                }
                p->updateBalance(netChange);
            }
        }
        for (const auto& p : players) buffer << "," << p->getBalance();
        buffer << "," << house->getBalance() << "\n";

        if (i % 10000 == 0) {
            outFile << buffer.str();
            buffer.str(""); 
            buffer.clear(); 
        }
        if (allPlayersBankrupt || house->isBankrupt()) break;
    }
    outFile << buffer.str();
    outFile.close();
}