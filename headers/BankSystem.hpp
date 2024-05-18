#ifndef PROG2_NHF_BANKSYSTEM_HPP
#define PROG2_NHF_BANKSYSTEM_HPP

#include "User.hpp"
#include "TContainer.hpp"
#include <fstream>
#include <sstream>

class BankSystem {
private: // Variables
    TContainer<User> users; // Stored Users of the bank
    TContainer<Share> bankShares; // Stored Shares of the bank
    Money bankMoney; // Banks Total money TODO check if needed
public:
    // Constructor, Destructors
    BankSystem();
    explicit BankSystem(const Money &initMoney);
    ~BankSystem() = default;

    //Getters

    [[nodiscard]] const Money &getBankMoney() const;
    [[nodiscard]] const TContainer<User> &getUsers() const;
    User & getUserByUsername(const std::string &username); // Gives back User object by username
    const User &getConstUser(const std::string &username); // Same as the previous but const (for read-only operations)

    //Get...By...

    [[nodiscard]] Share &getShareByChild(const OwnedShare &in) const; // TODO Shares

    // New Queries

    void addNewUser(const User &user); // Adds new users to the TContainer
    void deleteUser(const User &user); // Deletes user from TContainer
    void loadUsers(const TContainer<User> &usersIn); // Function used by FileManager to load users when starting

    void addBankShares(const Share &ShareIn); // TODO
    void deleteBankShares(const Share &ShareIn); // TODO

    [[nodiscard]] bool isUserNameReserved(const std::string &username) const; // Checks if username is in use already
};

#endif //PROG2_NHF_BANKSYSTEM_HPP
