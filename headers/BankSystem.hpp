#ifndef PROG2_NHF_BANKSYSTEM_HPP
#define PROG2_NHF_BANKSYSTEM_HPP

#include "BankAccount.hpp"
#include "TContainer.hpp"

class BankSystem {
private:
    TContainer<BankAccount> users;
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

    [[nodiscard]] Share& getShareByChild(const OwnedShare& in) const;

    // New Queries

    void addNewUser(const BankAccount& user);

};

#endif //PROG2_NHF_BANKSYSTEM_HPP
