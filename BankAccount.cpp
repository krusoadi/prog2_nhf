#include <random>
#include "BankAccount.h"



BankAccount::BankAccount(const BankAccount &other): ID(other.ID), userMoney(other.userMoney) {}

BankAccount::BankAccount(): ID(BankAccount::generateID()), userMoney() {}

void BankAccount::setMoney(const Money& in) {
    this->userMoney = in;
}

BankAccount::BankAccount(const Money& in): ID(BankAccount::generateID()) {
    if (in.getValue() < 0) {
        // TODO EXCEPTION ITT IS
    }
    this->userMoney = in;
}

Money BankAccount::getMoney() const {
    return userMoney;
}

unsigned int BankAccount::getId() const {
    return ID;
}

int BankAccount::generateID() {

    // Safe C++ 11 random generator

    std::random_device randomizer;
    std::mt19937 gen(randomizer());
    std::uniform_int_distribution<>dis(1,10000);

    return dis(gen);
}

void BankAccount::operator+=(const BankAccount &other) {
    this->userMoney = this->userMoney + other.userMoney;
}

const std::string &BankAccount::getName() const {
    return name;
}

void BankAccount::setName(const std::string &newUserName) {
    this->name = newUserName;
}


std::ostream& operator<<(std::ostream& stream, const BankAccount& in) {
    stream << "Name: " << in.getName() << " (" << in.getId() << ") :" << in.getMoney();
    return stream;
}
