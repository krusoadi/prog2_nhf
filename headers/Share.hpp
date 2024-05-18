#ifndef PROG2_NHF_SHARE_HPP
#define PROG2_NHF_SHARE_HPP

#include "Exceptions.hpp"
#include "Money.hpp"
#include "IDManager.hpp"

class OwnedShare;

class Share {
private:
    IDManager ShareID; // Generated id of the share, needed for OwnedShare verification
    std::string name; // Name of the Share e.g.: Apple Inc.
    Money value; // Current value of the share
    unsigned int available; // Number of available shares

    // New price (after sell/buy) calculators

    double static getNewRate(bool decrease); // Random growth/regression rate calculator
    void calculateNewPrice(int change); // Method to set the new price with the generated rate

public:
    // Constructors, Destructors

    Share();
    Share(std::string name, const Money &value, unsigned int available);
    Share(const Share &oth) = default;

    ~Share() = default;

    // Getters

    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] const Money &getValue() const;
    [[nodiscard]] unsigned int getAvailable() const;
    [[nodiscard]] int getShareId() const;

    // Share Buyer and Seller methods

    void buyFromUser(int n, OwnedShare &in);
    void sellToUser(int n, OwnedShare &in);

    // Slave identifier operator

    bool operator==(const OwnedShare &other) const;
    bool operator!=(const OwnedShare &other) const;
    bool operator==(const Share &other);
};

std::ostream &operator<<(std::ostream &stream, const Share &in);

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

    bool operator==(const Share &other) const;
    bool operator!=(const Share &other) const;

    // Get the price of the owned Share (needs the master to get the value, due to fluctuating prices)
    [[nodiscard]] Money showValue(Share *master) const;
};

std::ostream &operator<<(std::ostream &stream, const OwnedShare &in);


#endif //PROG2_NHF_SHARE_HPP
