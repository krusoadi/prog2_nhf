
#ifndef PROG2_NHF_SHARE_HPP
#define PROG2_NHF_SHARE_HPP
#include "Exceptions.hpp"
#include "Money.hpp"

class OwnedShare;

class Share {
private:
    int ShareID;
    std::string name; // Name of the Share e.g.: Apple Inc.
    Money value; // Current value of the share
    unsigned int available; // Number of available shares

    // Static ID generator, and current Highest ID, for unique values

    static int currentIDCounter;
    int static generateID() {if(!currentIDCounter) {initIDCounter();} return currentIDCounter++;}; // egh...
    void static initIDCounter () {currentIDCounter = 1;}; // TODO finishing and implementing

    // New price (after sell/buy) calculators

    double static getNewRate(bool decrease); // Random growth/regression rate calculator
    void calculateNewPrice(int change); // Method to set the new price with the generated rate

public:
    // Constructors, Destructors

    Share(std::string name, const Money &value, unsigned int available);
    ~Share() = default;

    // Getters

    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] const Money &getValue() const;
    [[nodiscard]] unsigned int getAvailable() const;

    // Share Buyer and Seller methods

    void sellShares(int n, OwnedShare& in);
    void buyShares(int n, OwnedShare& in);

    // Slave identifier operator

    bool operator==(const OwnedShare& other) const;
    bool operator!=(const OwnedShare& other) const;

    [[nodiscard]] int getShareId() const;

};

std::ostream& operator<<(std::ostream& stream, const Share &in);

class OwnedShare {
private:
    int masterShareID;
    int amount; // amount of bought shares
public:
    // Constructors, Destructors

    OwnedShare();
    explicit OwnedShare(int amount);

    // Getters

    [[nodiscard]] int getAmount() const;
    [[nodiscard]] int getMasterShareId() const;

    // Setters

    void setAmount(int amountIn);
    void setMasterShareId(int masterShareId);

    // Master identifier operators

    bool operator==(const Share& other) const;
    bool operator!=(const Share& other) const;


    // Methods to get information about the Share (Master)

    [[nodiscard]] Money showValue() const;
    [[nodiscard]] std::string showName() const;
};

std::ostream& operator<<(std::ostream& stream, const OwnedShare &in);


#endif //PROG2_NHF_SHARE_HPP
