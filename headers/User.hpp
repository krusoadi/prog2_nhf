#ifndef PROG2_NHF_USER_HPP
#define PROG2_NHF_USER_HPP
#include "TContainer.hpp"
#include "BankAccount.hpp"

class User {
private:
    std::string username;
    std::string hashedPw;
    BankAccount userBank;

public:
    //Constructor, Destructor
    User() = default;
    User(std::string username, std::string hashedPw, const BankAccount &userBank);
    User(const User&other) = default;
    ~User() = default;


    //Getters

    [[nodiscard]] const std::string &getUsername() const;
    [[nodiscard]] const BankAccount getUserBank() const;
    [[nodiscard]] bool MatchPassword(std::string password) const;

    //Setters

    void setUserBank(const BankAccount &userBankIn);
    void setHashedPw(const std::string &hashedPwIn);
    void setUsername(const std::string &usernameIn);

    bool operator==(const User& other);
};



#endif //PROG2_NHF_USER_HPP
