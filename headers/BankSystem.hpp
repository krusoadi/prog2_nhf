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

};

#endif //PROG2_NHF_BANKSYSTEM_HPP
