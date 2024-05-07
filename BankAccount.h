#ifndef PROG2_NHF_BANKACCOUNT_H
#define PROG2_NHF_BANKACCOUNT_H

#include "Money.h"
#include <string>



class BankAccount {
private:
    const unsigned int ID;
    std::string name;

    Money userMoney;

public:

    // Constructors/Destructors

    BankAccount();
    BankAccount(const Money& in);
    BankAccount(const BankAccount& other);
    ~BankAccount() = default;

    // Getters

    Money getMoney() const;
    unsigned int getId() const;
    const std::string &getName() const;

    // Setters

    void setMoney(const Money& in);
    void setName(const std::string &name);

    // Static functions

    static int generateID();

    // Operator overloads

    void operator+=(const BankAccount& other);

};

std::ostream& operator<<(std::ostream& stream, const BankAccount& in);



#endif //PROG2_NHF_BANKACCOUNT_H
