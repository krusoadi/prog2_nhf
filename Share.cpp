#include "Share.h"
#include <utility>
#include <random>

Share::Share(std::string name, const Money &value, unsigned int available) : name(std::move(name)), value(value),
                                                                                    available(available) {}

double Share::getNewRate(bool decrease) {

    // Safe C++ 11 random generator

    std::random_device randomizer;
    std::mt19937 gen(randomizer());

    int a, b;

    decrease ? a = 80 : a = 101 ;
    decrease ?  b = 100 : b = 135;

    std::uniform_int_distribution<>dis(a,b);

    return ((double)dis(gen)) / 100;
}

void Share::calculateNewPrice(int sold) {
    double rate = getNewRate(sold);
    this->value *= rate;
}

void Share::sellShares(int n, OwnedShare& in) {
    if (in.getAmount() < n) {
        throw Exceptions(NotEnoughShares, "There was not enough shares to sell");
    }
    if (in.getMaster() != this) {
        throw Exceptions(WrongMaster, "Tried to sell back share to a different one.");
    }
    this->available += n;
    calculateNewPrice(true);
    in.setAmount(in.getAmount() - n);
}

OwnedShare Share::buyShares(int n) {
    if (this->available >= n) {
        this->available -= n;
        calculateNewPrice(false);

        return {n, this};
    }
    return {0, nullptr};
}

const std::string &Share::getName() const {
    return name;
}

const Money &Share::getValue() const {
    return value;
}

unsigned int Share::getAvailable() const {
    return available;
}

// OwnedShare


int OwnedShare::getAmount() const {
    return amount;
}

void OwnedShare::setAmount(int amountIn) {
    this->amount = amountIn;
}

OwnedShare::OwnedShare( int amount, Share* masterIn): amount(amount), Master(masterIn) {}

Share *OwnedShare::getMaster() const {
    return Master;
}

void OwnedShare::setMaster(Share *master) {
    Master = master;
}

Money OwnedShare::showValue() const {
    return (*(this->getMaster())).getValue();
}

std::string OwnedShare::showName() const {
    return (*(this->getMaster())).getName();
}
