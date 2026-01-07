#include "auction_engine.h"
#include <algorithm>

double AdCandidate::getRank() const {
    return maxBid * qualityScore;
}

AuctionResult GSPStrategy::determineWinner(std::vector<AdCandidate>& candidates) {
    if (candidates.empty()) return {false, "", 0.0};

    std::sort(candidates.begin(), candidates.end(), 
        [](const AdCandidate& a, const AdCandidate& b) {
            return a.getRank() > b.getRank();
        });

    const AdCandidate& winner = candidates[0];
    double priceToPay = 0.01;

    if (candidates.size() > 1) {
        const AdCandidate& runnerUp = candidates[1];
        priceToPay = (runnerUp.getRank() / winner.qualityScore) + 0.01;
    }

    if (priceToPay > winner.maxBid) priceToPay = winner.maxBid;

    return {true, winner.id, priceToPay};
}