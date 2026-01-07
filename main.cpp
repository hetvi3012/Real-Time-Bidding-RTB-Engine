#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include "budget_manager.h"  // Include the header, NOT the cpp
#include "auction_engine.h"  // Include the header, NOT the cpp

// Global Shared Resources
BudgetManager globalBudgetManager;
GSPStrategy globalStrategy;

std::atomic<int> totalAuctions(0);
std::atomic<int> successfulSales(0);
std::atomic<int> failedBudgetDeductions(0);

void handleAdRequest(int threadId) {
    std::vector<AdCandidate> auctionCandidates = {
        {"Nike",    2.00, 5.0}, 
        {"Adidas",  3.00, 3.0}, 
        {"Puma",    1.50, 4.0}  
    };

    AuctionResult result = globalStrategy.determineWinner(auctionCandidates);

    if (result.hasWinner) {
        bool success = globalBudgetManager.attemptPurchase(result.winnerId, result.winningPrice);
        if (success) {
            successfulSales++;
        } else {
            failedBudgetDeductions++;
        }
    }
    totalAuctions++;
}

int main() {
    std::cout << "--- Starting Modular Ad Server ---" << std::endl;

    globalBudgetManager.addBudget("Nike", 100.00);
    globalBudgetManager.addBudget("Adidas", 50.00);
    globalBudgetManager.addBudget("Puma", 50.00);

    std::vector<std::thread> trafficThreads;
    int numThreads = 10;        
    int requestsPerThread = 100; 

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numThreads; ++i) {
        trafficThreads.push_back(std::thread([i, requestsPerThread]() {
            for (int r = 0; r < requestsPerThread; ++r) {
                handleAdRequest(i);
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }));
    }

    for (auto& t : trafficThreads) {
        t.join();
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;

    std::cout << "\n--- Simulation Finished ---" << std::endl;
    std::cout << "Time Elapsed: " << elapsed.count() << " seconds" << std::endl;
    std::cout << "Total Auctions: " << totalAuctions << std::endl;
    std::cout << "Successful Sales: " << successfulSales << std::endl;
    std::cout << "Missed Opportunities: " << failedBudgetDeductions << std::endl;

    return 0;
}