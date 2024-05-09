#include "../headers/Share.hpp"
#include <utility>
#include <random>


Share::Share(std::string name, const Money &value, unsigned int available) : name(std::move(name)), value(value),
                                                                                    available(available) {}

double Share::getNewRate(bool decrease) {
    // Safe C++ 11 random generator

    std::random_device randomizer;
    std::mt19937 gen(randomizer());

    int a, b;

    decrease ? a = 85 : a = 101;
    decrease ?  b = 99 : b = 115;

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

void Share::buyShares(int n, OwnedShare& in) {
    if (in.getMaster() != nullptr && in.getMaster() != this) {
        throw Exceptions(WrongMaster, "Tried to buy share to a different one.");
    }
    if (this->available >= n) {
        this->available -= n;
        in.setMaster(this);
        in.setAmount(in.getAmount() + n);
        calculateNewPrice(false);
        return;
    }
    throw Exceptions(NotEnoughShares, "There weren't enough shares to buy");
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

OwnedShare::OwnedShare(): amount(0), Master(nullptr) {}


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
    Money value = this->getMaster()->getValue();

    return  value * this->amount;
}

std::string OwnedShare::showName() const {
    return this->getMaster()->getName();
}

std::ostream &operator<<(std::ostream &stream, const Share &in) {
    return stream << in.getName() << " (available: " << in.getAvailable() <<") Price: " << in.getValue();
}

std::ostream &operator<<(std::ostream &stream, const OwnedShare &in) {
    return stream << in.showName() << " owned: "<< in.getAmount() << " total price: " << in.showValue();
}
