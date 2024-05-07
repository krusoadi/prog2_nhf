#include <random>
#include <utility>
#include "BankAccount.h"



BankAccount::BankAccount(const BankAccount &other): ID(other.ID), userMoney(other.userMoney) {}

BankAccount::BankAccount(): ID(BankAccount::generateID()), userMoney(), isMale(false), userShares(nullptr), boughtShares(0) {}

BankAccount::BankAccount(const Money& in, std::string nameIn, bool isMaleIn): ID(BankAccount::generateID()), name(std::move(nameIn)) {
    if (in.getValue() < 0) {
        throw Exceptions(NegativeMoney, "Negative money was given.");
    }
    this->userMoney = in;
    this->isMale = isMaleIn;
    this->userShares = nullptr;
    this->boughtShares = 0;
}


Money BankAccount::getMoney() const {
    return userMoney;
}


const std::string &BankAccount::getName() const {
    return name;
}

unsigned int BankAccount::getId() const {
    return ID;
}

void BankAccount::setMoney(const Money& in) {
    this->userMoney = in;
}

int BankAccount::generateID() {

    // Safe C++ 11 random generator

    std::random_device randomizer;
    std::mt19937 gen(randomizer());
    std::uniform_int_distribution<>dis(1000,9999);

    return dis(gen);
}

void BankAccount::operator+=(const BankAccount &other) {
    this->userMoney = this->userMoney + other.userMoney;
}



void BankAccount::setName(const std::string &newUserName) {
    this->name = newUserName;
}

void BankAccount::addMoney(const Money &in) {
    this->userMoney += in;
}

void BankAccount::substractMoney(const Money &in) {
    this->userMoney -= in;
}

std::string BankAccount::getGender() const {
    if (isMale) {
        return {"Male"};
    }
    return {"Female"};
}

bool BankAccount::getisWorker() const {
    return isWorker;
}

void BankAccount::setIsWorker(bool isWorkerIn) {
    BankAccount::isWorker = isWorkerIn;
}

void BankAccount::BuyShares(Share& type, int amount) { // TODO bugos
    if (this->userShares == nullptr) {
        this->userShares = new OwnedShare[1];
        *this->userShares = type.buyShares(amount);
        boughtShares = 1;
    }
}

void BankAccount::SellShares(Share& type, int amount) { //TODO bugos
    if (this->userShares != nullptr) {
        type.sellShares(amount, this->userShares[0]);
        /*
        if (this->userShares[0].getAmount() - amount == 0) {
            delete this->userShares;
            this->boughtShares = 0;
        }
         */
    }
}

OwnedShare *BankAccount::getUserShares() const {
    return userShares;
}


std::ostream& operator<<(std::ostream& stream, const BankAccount& in) {
    stream << "Name: " << in.getName() << " (id: " << in.getId() << ") " << in.getGender() <<" : " << in.getMoney();
    return stream;
}
