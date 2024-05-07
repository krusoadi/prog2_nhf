
#ifndef PROG2_NHF_SHARE_HPP
#define PROG2_NHF_SHARE_HPP
#include "Exceptions.hpp"
#include "Money.hpp"
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
    void buyShares(int n, OwnedShare& in);

};

class OwnedShare {
private:
    int amount;
    Share* Master; // o a share, amit vettunk beolvasaskor erre figyelni kell
public:
    OwnedShare();

    OwnedShare(int amount, Share* masterIn);

    // Getters

    int getAmount() const;
    Share *getMaster() const;

    // Setters

    void setAmount(int amountIn);
    void setMaster(Share *master);

    Money showValue() const;
    std::string showName() const;
};


#endif //PROG2_NHF_SHARE_HPP
