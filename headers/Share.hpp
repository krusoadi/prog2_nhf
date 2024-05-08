
#ifndef PROG2_NHF_SHARE_HPP
#define PROG2_NHF_SHARE_HPP
#include "Exceptions.hpp"
#include "Money.hpp"

class OwnedShare;

class Share {
private:
    std::string name; // Name of the Share e.g.: Apple Inc.
    Money value; // Current value of the share
    unsigned int available; // Number of available shares

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

    // Share buyer and Seller methods

    void sellShares(int n, OwnedShare& in);
    void buyShares(int n, OwnedShare& in);

};

std::ostream& operator<<(std::ostream& stream, const Share &in);

class OwnedShare {
private:
    int amount; // amount of bought shares
    Share* Master; // The Share objects pointer which it's connected to
public:
    // Constructors, Destructors

    OwnedShare();
    OwnedShare(int amount, Share* masterIn);

    // Getters

    [[nodiscard]] int getAmount() const;
    [[nodiscard]] Share *getMaster() const;

    // Setters

    void setAmount(int amountIn);
    void setMaster(Share *master);

    // Methods to get information about the Share (Master)

    [[nodiscard]] Money showValue() const;
    [[nodiscard]] std::string showName() const;
};

std::ostream& operator<<(std::ostream& stream, const OwnedShare &in);


#endif //PROG2_NHF_SHARE_HPP
