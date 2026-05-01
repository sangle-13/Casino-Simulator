#include "Simulator.h"
#include "PlayerFactory.h"
#include "House.h"
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <chrono>
#include <cstdlib>

void runSimulationNode(int threadID, int numSimulations, double houseBalance, const std::string& prefix) {
    std::string fileName = prefix + "_" + std::to_string(threadID) + ".csv";

    auto house = std::make_unique<House>("NhaCai", houseBalance);
    Simulator sim(numSimulations, fileName, std::move(house));

    sim.addPlayer(PlayerFactory::createPlayer(PlayerFactory::Type::CHUNG_THUY, "ChungThuy", 800000.0));
    sim.addPlayer(PlayerFactory::createPlayer(PlayerFactory::Type::RAI_THAM, "RaiTham", 800000.0));

    sim.run();
}

int main() {
    int totalSimulations = 100000000;

    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads < 2) numThreads = 4;

    unsigned int halfThreads = numThreads / 2;
    int simsPerThread = totalSimulations / halfThreads;

    std::cout << "=================================================\n";
    std::cout << " MO PHONG DA LUONG TICH HOP\n";
    std::cout << "=================================================\n";
    std::cout << "[-] Phat hien CPU co " << numThreads << " luong.\n";
    std::cout << "[-] Chia " << halfThreads << " luong cho Nha Cai NHO \n";
    std::cout << "[-] Chia " << halfThreads << " luong cho Nha Cai LON \n";
    std::cout << "[!] Dang chay song song... Vui long doi!\n";

    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> workers;

    for (unsigned int i = 1; i <= halfThreads; ++i) {
        workers.push_back(std::thread(runSimulationNode, i, simsPerThread, 15000.0, "data_nho"));
    }

    for (unsigned int i = 1; i <= halfThreads; ++i) {
        workers.push_back(std::thread(runSimulationNode, i, simsPerThread, 6000000.0, "data_lon"));
    }

    for (auto& t : workers) {
        t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "-------------------------------------------------\n";
    std::cout << "[+] Mo phong hoan tat 100%!\n";
    std::cout << "[+] Thoi gian chay thuc te: " << elapsed.count() << " giay.\n";
    std::cout << "-------------------------------------------------\n";
    std::cout << "Dang khoi chay he thong bieu do Python...\n";

    std::system("python scripts/bao_cao_nhacai_nho.py");
    std::system("python scripts/bao_cao_nhacai_lon.py");

    return 0;
}