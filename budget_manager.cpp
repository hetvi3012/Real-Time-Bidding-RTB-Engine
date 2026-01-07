#include "budget_manager.h"

void BudgetManager::addBudget(const std::string& advertiserId, double amount) {
    std::lock_guard<std::mutex> lock(mtx);
    budgetMap[advertiserId] += amount;
}

bool BudgetManager::attemptPurchase(const std::string& advertiserId, double amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (budgetMap.find(advertiserId) == budgetMap.end()) return false;
    
    if (budgetMap[advertiserId] >= amount) {
        budgetMap[advertiserId] -= amount;
        return true;
    }
    return false;
}

double BudgetManager::getRemainingBudget(const std::string& advertiserId) {
    std::lock_guard<std::mutex> lock(mtx);
    if (budgetMap.find(advertiserId) != budgetMap.end()) {
        return budgetMap[advertiserId];
    }
    return 0.0;
}