#include <utility>
#include <random>
#include "../headers/memtrace.h"
#include "../headers/Share.hpp"
Share::Share(std::string name, const Money &value, unsigned int available) :ShareID(IDManager()),name(std::move(name)),
                                                                            value(value), available(available) {}


Share::Share(int idIn, std::string name, const Money &value, unsigned int available) :  ShareID(IDManager(idIn)), name(std::move(name)),
                                                                                        value(value), available(available) {}

Share::Share() : value(Money()), available(0) {}

double Share::getNewRate(bool decrease) {
    std::random_device randomizer;
    std::mt19937 gen(randomizer());

    int low, high;

    // we decide the ranges of the random new rate based on if it was sold or bought

    decrease ? low = 95 : low = 100;
    decrease ? high = 99 : high = 105;

    std::uniform_int_distribution<> dis(low, high);

    return ((double) dis(gen)) / 100;
}

void Share::calculateNewPrice(bool sold) {
    double rate = getNewRate(sold);
    this->value *= rate;
}

void Share::buyFromUser(int n, OwnedShare &in) {
    if (in.getAmount() < n) {
        throw Exceptions(NotEnoughShares, "There was not enough shares to sell");
    }
    if (in.getMasterShareId() != this->ShareID.getId()) {
        throw Exceptions(WrongMaster, "Tried to sell back share to a different one.");
    }
    this->available += n;
    calculateNewPrice(true);
    in.setAmount(in.getAmount() - n);
}

void Share::sellToUser(int n, OwnedShare &in) {
    if (in.getMasterShareId() != -1 && in.getMasterShareId() != this->ShareID.getId()) {
        throw Exceptions(WrongMaster, "\nTried to buy share to a different one.\n");
    }
    if ((int)this->available >= n) { // cannot be too high to have a signed cast
        this->available -= n;
        in.setMasterShareId(this->ShareID.getId());
        in.setAmount(in.getAmount() + n);

        calculateNewPrice(false);
        return;
    }
    throw Exceptions(NotEnoughShares, "\nThere weren't enough shares to buy\n");
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
    return ShareID.getId();
}

bool Share::operator==(const OwnedShare &other) const {
    return this->ShareID.getId() == other.getMasterShareId();
}

bool Share::operator!=(const OwnedShare &other) const {
    return this->ShareID.getId() != other.getMasterShareId();
}

bool Share::operator==(const Share &other) {
    return this->ShareID == other.ShareID;
}

// OwnedShare

OwnedShare::OwnedShare() : masterShareID(-1), amount(0) {}

OwnedShare::OwnedShare(int amount) : masterShareID(-1), amount(amount) {}

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

Money OwnedShare::showValue(Share *master) const {
    return Money(master->getValue()) * this->amount;

}

std::ostream &operator<<(std::ostream &stream, const Share &in) {
    return stream << in.getName() << " (available: " << in.getAvailable() << ") Price: " << in.getValue();
}

std::ostream &operator<<(std::ostream &stream, const OwnedShare &in) {
    return stream << "(id of share: " << in.getMasterShareId() << ") owned: " << in.getAmount();
}
