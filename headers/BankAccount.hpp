#ifndef PROG2_NHF_BANKACCOUNT_HPP
#define PROG2_NHF_BANKACCOUNT_HPP

#include "Share.hpp"
#include "TContainer.hpp"

class BankAccount {
private:
    // Data of the user

    const unsigned int ID;
    std::string name;
    bool isMale;
    Money userMoney;
    bool isWorker;

    // Bought shares of the user stored in a vector

    std::vector<OwnedShare> userShares;

public:

    // Constructors/Destructors

    BankAccount();
    BankAccount(const Money& money, std::string name, bool isMale, bool isWorker);
    BankAccount(const BankAccount& other);

    ~BankAccount() = default;

    // Getters

    [[nodiscard]] Money getMoney() const;
    [[nodiscard]] unsigned int getId() const;
    [[nodiscard]] const std::string& getName() const;

    [[nodiscard]] std::string getGender() const;
    [[nodiscard]] bool getisWorker() const;


    // Setters

    void setMoney(const Money& in);
    void setName(const std::string &name);
    void setIsWorker(bool isWorkerIn);

    // Static ID generator method

    static int getGeneratedID();

    // Money managing methods

    void addMoney(const Money& in);
    void subtractMoney(const Money& in);

    // Share managing functions

    void BuyShares(Share& type, int amount);
    void SellShares(Share& type, int amount);

    // Share printer (Debug purposes)

    void revealShares();
};

std::ostream& operator<<(std::ostream& stream, const BankAccount& in);

#endif //PROG2_NHF_BANKACCOUNT_HPP
