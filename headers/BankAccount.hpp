#ifndef PROG2_NHF_BANKACCOUNT_HPP
#define PROG2_NHF_BANKACCOUNT_HPP

#include "Share.hpp"
#include <string>
#include <vector>

class BankAccount {
private:
    const unsigned int ID;
    std::string name;
    bool isMale;
    Money userMoney;

    bool isWorker; // TODO Implementalni

    std::vector<OwnedShare> userShares;

public:

    // Constructors/Destructors

    BankAccount();
    BankAccount(const Money& money, std::string name, bool isMale, bool isWorker);
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

    // Money Functions

    void addMoney(const Money& in);
    void substractMoney(const Money& in);

    // Other Functions

    std::string getGender() const;

    bool getisWorker() const;

    void setIsWorker(bool isWorkerIn);

    // Share functions

    void BuyShares(Share& type, int amount);
    void SellShares(Share& type, int amount);

    void revealShares();
};

std::ostream& operator<<(std::ostream& stream, const BankAccount& in);



#endif //PROG2_NHF_BANKACCOUNT_HPP