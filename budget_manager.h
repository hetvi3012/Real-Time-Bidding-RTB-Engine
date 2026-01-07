#ifndef BUDGET_MANAGER_H
#define BUDGET_MANAGER_H

#include <string>
#include <unordered_map>
#include <mutex>

class BudgetManager {
private:
    std::unordered_map<std::string, double> budgetMap;
    std::mutex mtx; 

public:
    void addBudget(const std::string& advertiserId, double amount);
    bool attemptPurchase(const std::string& advertiserId, double amount);
    double getRemainingBudget(const std::string& advertiserId);
};

#endif