#include "../headers/BankSystem.hpp"

BankSystem::BankSystem(): bankMoney(Money()), users(TContainer<User>()),
                          bankShares(TContainer<Share>())  {}

BankSystem::BankSystem(const Money &initMoney): users(TContainer<User>()),
                          bankShares(TContainer<Share>()), bankMoney(initMoney) {}

const Money &BankSystem::getBankMoney() const {
    return bankMoney;
}

Share &BankSystem::getShareByChild(const OwnedShare& in) const {
    return this->bankShares[this->bankShares.search(in)];
}

void BankSystem::addNewUser(const User& user) {
    try {this->users.add_back(user);}
    catch (Exceptions &e) {std::cerr << e.what() << " Didn't add new user.\n";}
}

void BankSystem::addBankShares(const Share &ShareIn) {
    try {this->bankShares.add_back(ShareIn);}
    catch (Exceptions &e) {std::cerr << e.what() << " Didn't add new Share.\n";}
}

void BankSystem::deleteUser(const User &user) {
    try {this->users.pop_index(this->users.search(user));}
    catch (Exceptions &e) {std::cerr << e.what() << " Didn't delete User.\n";}
}

void BankSystem::deleteBankShares(const Share &ShareIn) {
    try {this->bankShares.pop_index(this->bankShares.search(ShareIn));}
    catch (Exceptions &e) {std::cerr << e.what() << " Didn't delete Share.\n";}
}

void BankSystem::loadUsers(const std::string& filename) {
    std::ifstream userFile(filename, std::ios::in);

    if (!userFile.is_open()) {
        throw Exceptions(FileError, "Couldn't open user info file, are you sure it exists?");
    }

    for (std::string line; std::getline(userFile, line);) {
        std::string fUsername;
        std::string fPassword;
        std::string fAccId;

        std::istringstream lineStream(line);

        std::getline(lineStream, fUsername, ':');
        std::getline(lineStream, fPassword, ':');
        std::getline(lineStream, fAccId, ':');

        User readIn(fUsername, fPassword, BankAccount(IDManager(std::stoi(fAccId))));

        users.add_back(readIn);
    }
}

