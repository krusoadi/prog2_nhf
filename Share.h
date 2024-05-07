
#ifndef PROG2_NHF_SHARE_H
#define PROG2_NHF_SHARE_H
#include "Exceptions.h"
#include "Money.h"
#include <string>

class OwnedShare;

class Share {
private:
    std::string name;
    Money value;
    unsigned int available;

    double static getNewRate(bool decrease);
    void calculateNewPrice(int change);

public:
    // Getters

    const std::string &getName() const;
    const Money &getValue() const;
    unsigned int getAvailable() const;

    Share(std::string name, const Money &value, unsigned int available);

    void sellShares(int n, OwnedShare& in);
    OwnedShare buyShares(int n);

};

class OwnedShare {
private:
    int amount;
    Share* Master;
public:
    OwnedShare() = default;

    OwnedShare(int amount, Share* masterIn);

    // Getters

    int getAmount() const;
    Share *getMaster() const;

    // Setters

    void setAmount(int amount);
    void setMaster(Share *master);

    Money showValue();
    std::string showName();
};


#endif //PROG2_NHF_SHARE_H
