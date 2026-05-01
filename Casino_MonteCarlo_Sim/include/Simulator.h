#pragma once
#include "Player.h"
#include "House.h"
#include <vector>
#include <memory>
#include <string>

class Simulator {
private:
    int numSimulations;
    std::string outputFileName;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<House> house;

public:
    Simulator(int nums, const std::string& fileName, std::unique_ptr<House> h)
        : numSimulations(nums), outputFileName(fileName), house(std::move(h)) {
    }

    void addPlayer(std::unique_ptr<Player> p);
    void run();
};