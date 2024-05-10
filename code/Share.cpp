#include "../headers/Share.hpp"
#include <utility>
#include <random>

int Share::currentIDCounter = 0; // TODO method for this!

Share::Share(std::string name, const Money &value, unsigned int available) : name(std::move(name)), value(value),
available(available), ShareID(generateID()) {}

double Share::getNewRate(bool decrease) {
    std::random_device randomizer;
    std::mt19937 gen(randomizer());

    int low, high;

    decrease ? low = 95 : low = 100;
    decrease ? high = 99 : high = 105;

    std::uniform_int_distribution<>dis(low, high);

    return ((double)dis(gen)) / 100;
}

void Share::calculateNewPrice(int sold) {
    double rate = getNewRate(sold);
    this->value *= rate;
}

void Share::buyFromUser(int n, OwnedShare& in) {
    if (in.getAmount() < n) {
        throw Exceptions(NotEnoughShares, "There was not enough shares to sell");
    }
    if (in.getMasterShareId() != this->ShareID) {
        throw Exceptions(WrongMaster, "Tried to sell back share to a different one.");
    }
    this->available += n;
    calculateNewPrice(true);
    in.setAmount(in.getAmount() - n);
}

void Share::sellToUser(int n, OwnedShare& in) {
    if (in.getMasterShareId() != -1 && in.getMasterShareId() != this->ShareID) {
        throw Exceptions(WrongMaster, "Tried to buy share to a different one.");
    }
    if (this->available >= n) {
        this->available -= n;
        in.setMasterShareId(this->ShareID);
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

int Share::getShareId() const {
    return ShareID;
}

bool Share::operator==(const OwnedShare &other) const {
    return this->ShareID == other.getMasterShareId();
}

bool Share::operator!=(const OwnedShare &other) const {
    return this->ShareID != other.getMasterShareId();
}

// OwnedShare

OwnedShare::OwnedShare(): amount(0), masterShareID(-1) {}

OwnedShare::OwnedShare(int amount): amount(amount), masterShareID(-1)  {}

int OwnedShare::getMasterShareId() const {
    return masterShareID;
}

int OwnedShare::getAmount() const {
    return amount;
}

void OwnedShare::setAmount(int amountIn) {
    this->amount = amountIn;
}

void OwnedShare::setMasterShareId(int masterShareId) {
    masterShareID = masterShareId;
}

bool OwnedShare::operator==(const Share &other) const {
    return this->masterShareID == other.getShareId();
}

bool OwnedShare::operator!=(const Share &other) const {
    return this->masterShareID != other.getShareId();
}

Money OwnedShare::showValue(Share* master) const {
    return Money(master->getValue()) * this->amount;

}

std::ostream &operator<<(std::ostream &stream, const Share &in) {
    return stream << in.getName() << " (available: " << in.getAvailable() <<") Price: " << in.getValue();
}

std::ostream &operator<<(std::ostream &stream, const OwnedShare &in) {
    return stream << "id of share: " << in.getMasterShareId() << " owned: "<< in.getAmount();
}
