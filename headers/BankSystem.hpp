#ifndef PROG2_NHF_BANKSYSTEM_HPP
#define PROG2_NHF_BANKSYSTEM_HPP

#include "User.hpp"
#include "TContainer.hpp"
#include <fstream>
#include <sstream>

class BankSystem {
private: // Variables
    TContainer<User> users;
    TContainer<Share> bankShares;
    Money bankMoney;
public:
    // Constructor, Destructors

    BankSystem();
    explicit BankSystem(const Money& initMoney);
    ~BankSystem() = default;

    //Getters TODO

    [[nodiscard]] const Money &getBankMoney() const;
    [[nodiscard]] const TContainer<User> &getUsers() const;

    //Get...By...

    [[nodiscard]] Share& getShareByChild(const OwnedShare& in) const; //TODO error handling (ptr approach or dummy-reference)

    // New Queries

    void addNewUser(const User& user);
    void addBankShares(const Share& ShareIn);

    void deleteUser(const User& user);
    void deleteBankShares(const Share& ShareIn);

    void loadUsers(const TContainer<User>& usersIn);

    const User& searchByUserName(const std::string& username);
    [[nodiscard]] bool isUserNameReserved(const std::string& username) const;
};

#endif //PROG2_NHF_BANKSYSTEM_HPP
