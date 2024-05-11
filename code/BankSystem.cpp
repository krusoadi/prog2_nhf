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
    try {this->users.add_back(user);}
    catch (Exceptions &e) {std::cerr << e.what() << " Didn't add new user.\n";}
}

void BankSystem::addBankShares(const Share &ShareIn) {
    try {this->bankShares.add_back(ShareIn);}
    catch (Exceptions &e) {std::cerr << e.what() << " Didn't add new Share.\n";}
}

void BankSystem::deleteUser(const BankAccount &user) {
    try {this->users.pop_index(this->users.search(user));}
    catch (Exceptions &e) {std::cerr << e.what() << " Didn't delete User.\n";}
}

void BankSystem::deleteBankShares(const Share &ShareIn) {
    try {this->bankShares.pop_index(this->bankShares.search(ShareIn));}
    catch (Exceptions &e) {std::cerr << e.what() << " Didn't delete Share.\n";}
}

