#ifndef AUCTION_ENGINE_H
#define AUCTION_ENGINE_H

#include <vector>
#include <string>

struct AdCandidate {
    std::string id;
    double maxBid;
    double qualityScore;
    double getRank() const;
};

struct AuctionResult {
    bool hasWinner;
    std::string winnerId;
    double winningPrice;
};

class PricingStrategy {
public:
    virtual AuctionResult determineWinner(std::vector<AdCandidate>& candidates) = 0;
    virtual ~PricingStrategy() = default;
};

class GSPStrategy : public PricingStrategy {
public:
    AuctionResult determineWinner(std::vector<AdCandidate>& candidates) override;
};

#endif