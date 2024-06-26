#include "../headers/BankSystem.hpp"

BankSystem::BankSystem() : users(TContainer<User>()),
                           bankShares(TContainer<Share>()), bankMoney(Money()) {}

BankSystem::BankSystem(const Money &initMoney) : users(TContainer<User>()),
                                                 bankShares(TContainer<Share>()), bankMoney(initMoney) {}

[[maybe_unused]] const Money &BankSystem::getBankMoney() const {
    return bankMoney;
}

Share &BankSystem::getShareByChild(const OwnedShare &in) const {
    return this->bankShares[this->bankShares.search(in)];
}

void BankSystem::addNewUser(const User &user) {
    try { this->users.add_back(user); }
    catch (Exceptions &e) { std::cerr << e.what() << " Didn't add new user.\n"; }
}

[[maybe_unused]] void BankSystem::addBankShares(const Share &ShareIn) {
    try { this->bankShares.add_back(ShareIn); }
    catch (Exceptions &e) { std::cerr << e.what() << " Didn't add new Share.\n"; }
}

[[maybe_unused]] void BankSystem::deleteUser(const User &user) {
    try { this->users.pop_index(this->users.search(user)); }
    catch (Exceptions &e) { std::cerr << e.what() << " Didn't delete User.\n"; }
}

[[maybe_unused]] void BankSystem::deleteBankShares(const Share &ShareIn) {
    try { this->bankShares.pop_index(this->bankShares.search(ShareIn)); }
    catch (Exceptions &e) { std::cerr << e.what() << " Didn't delete Share.\n"; }
}

void BankSystem::loadUsers(const TContainer<User> &usersIn) {
    this->users = usersIn;
}

const TContainer<User> &BankSystem::getUsers() const {
    return users;
}

const User &BankSystem::getConstUser(const std::string &username) {
    // Main reason for this is read only operations with ConstIterators ofr safety
    if (!users.isEmpty()) {
        for (const auto &it: users) {
            if (it.getUsername() == username) {
                return it;
            }
        }
    }
    throw Exceptions(UserNotFound, "Couldn't find user.");
}

bool BankSystem::isUserNameReserved(const std::string &username) const {
    if (users.isEmpty()) {
        return false;
    }
    for (const auto &it: users) {
        if (it.getUsername() == username) {
            return true;
        }
    }
    return false;
}

User &BankSystem::getUserByUsername(const std::string &username) {
    if (!users.isEmpty()) {
        for (auto &it: users) {
            if (it.getUsername() == username) {
                return it;
            }
        }
    }
    throw Exceptions(UserNotFound, "Couldn't find user.");
}

void BankSystem::loadBankShares(const TContainer<Share> &sharesIn) {
    this->bankShares = sharesIn;
}

const TContainer<Share> &BankSystem::getBankShares() const {
    return this->bankShares;
}

