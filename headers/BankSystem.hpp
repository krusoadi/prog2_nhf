#ifndef PROG2_NHF_BANKSYSTEM_HPP
#define PROG2_NHF_BANKSYSTEM_HPP

#include "User.hpp"
#include "TContainer.hpp"
#include <fstream>
#include <sstream>

class BankSystem {
private:
    TContainer<User> users;
    TContainer<Share> bankShares;
    Money bankMoney;
public:
    // Constructor, Destructors

    BankSystem();
    BankSystem(const Money& initMoney);
    ~BankSystem() = default;

    //Getters TODO

    [[nodiscard]] const Money &getBankMoney() const;

    //Get...By...

    [[nodiscard]] Share& getShareByChild(const OwnedShare& in) const; //TODO error handling (ptr approach or dummy-reference)

    // New Queries



    void addNewUser(const User& user);
    void addBankShares(const Share& ShareIn);

    void deleteUser(const User& user);
    void deleteBankShares(const Share& ShareIn);

    void loadUsers(const std::string& filename);
    void loadBankAccounts(const std::string& filename);
    void loadOwnedShares(const std::string& filename);

};

#endif //PROG2_NHF_BANKSYSTEM_HPP
