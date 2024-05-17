#include <utility>

#include "../headers/User.hpp"

User::User(std::string username, std::string hashedPw, const BankAccount &userBank) :
username(std::move(username)), hashedPw(std::move(hashedPw)), userBank(userBank) {}

const std::string &User::getUsername() const {
    return username;
}

void User::setUsername(const std::string &usernameIn) {
    User::username = usernameIn;
}

const std::string &User::getHashedPw() const {
    return hashedPw;
}

void User::setHashedPw(const std::string &hashedPwIn) {
    User::hashedPw = hashedPwIn;
}

BankAccount User::getUserBank() const {
    return userBank;
}

void User::setUserBank(const BankAccount &userBankIn) {
    User::userBank = userBankIn;
}

bool User::operator==(const User &other) {
    return (this->username == other.username) && (this->userBank == other.userBank);
}

bool User::MatchPassword(std::string password) const {
    return this->hashedPw == password;
}

