#include "../headers/BankSystem.hpp"

BankSystem::BankSystem(): bankMoney(Money()), users(TContainer<BankAccount>()),
                          bankShares(TContainer<Share>())  {}

BankSystem::BankSystem(const Money &initMoney): users(TContainer<BankAccount>()),
                          bankShares(TContainer<Share>()), bankMoney(initMoney) {}

const Money &BankSystem::getBankMoney() const {
    return bankMoney;
}

Share &BankSystem::getShareByChild(const OwnedShare& in) const {
    return this->bankShares[this->bankShares.search(in)];
}

void BankSystem::addNewUser(const BankAccount& user) {
    this->users.add_back(user);
}

