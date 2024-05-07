#include <random>
#include "BankAccount.h"

double BankAccount::getMoney() const {
    return money;
}

void BankAccount::setMoney(double amount) {
    this->money = amount;
}

int BankAccount::generateID() {

    // Safe C++ 11 random generator

    std::random_device randomizer;
    std::mt19937 gen(randomizer());
    std::uniform_int_distribution<>dis(1,10000);

    return dis(gen);
}

BankAccount::BankAccount(double amount, BankMoneyTypes curr): ID(BankAccount::generateID()) {
    if (amount >= 0) {
        this->money = amount;
        this->currency = curr;
    }
}

BankMoneyTypes BankAccount::getCurrency() const {
    return currency;
}

void BankAccount::setCurrency(BankMoneyTypes currency) {
    this->currency = currency;
}

unsigned int BankAccount::getId() const {
    return ID;
}

BankAccount::BankAccount(const BankAccount &other): ID(other.ID), money(other.money), currency(other.currency) {}

BankAccount::BankAccount(): ID(BankAccount::generateID()), money(0), currency(HUF) {}

void BankAccount::operator+(const BankAccount &other) {

}
