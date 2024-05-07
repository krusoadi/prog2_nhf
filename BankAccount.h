#ifndef PROG2_NHF_BANKACCOUNT_H
#define PROG2_NHF_BANKACCOUNT_H

#include "Share.h"
#include <string>

class BankAccount {
private:
    const unsigned int ID;
    std::string name;
    bool isMale;
    Money userMoney;

    bool isWorker;
public:

    // Constructors/Destructors

    BankAccount();
    BankAccount(const Money& in, std::string nameIn, bool isMaleIn);
    BankAccount(const BankAccount& other);
    ~BankAccount() = default;

    // Getters

    Money getMoney() const;
    unsigned int getId() const;
    const std::string& getName() const;

    // Setters

    void setMoney(const Money& in);
    void setName(const std::string &name);

    // Static functions

    static int generateID();

    // Operator overloads

    void operator+=(const BankAccount& other);

    void addMoney(const Money& in);
    void substractMoney(const Money& in);

    // Other Functions

    std::string getGender() const;

    bool getisWorker() const;

    void setIsWorker(bool isWorkerIn);

};

std::ostream& operator<<(std::ostream& stream, const BankAccount& in);



#endif //PROG2_NHF_BANKACCOUNT_H
