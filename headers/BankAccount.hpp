#ifndef PROG2_NHF_BANKACCOUNT_HPP
#define PROG2_NHF_BANKACCOUNT_HPP

#include "Share.hpp"
#include "TContainer.hpp"

class BankAccount {
private:
    // Data of the user

    IDManager ID;
    std::string name;
    bool isMale;
    Money userMoney;
    bool isWorker;

    // Bought shares of the user stored in a vector

    TContainer<OwnedShare> userShares;

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
    [[maybe_unused]] [[nodiscard]] bool getIsWorker() const;


    // Setters

    [[maybe_unused]] void setMoney(const Money& in);
    [[maybe_unused]] void setName(const std::string &name);
    [[maybe_unused]] void setIsWorker(bool isWorkerIn);

    // Money managing methods

    void addMoney(const Money& in);
    void subtractMoney(const Money& in);

    // Share managing functions

    void BuyShares(Share& SType, int amount);
    void SellShares(Share& SType, int amount);

    // Share printer (Debug purposes)

    void revealShares();

    // Operators

    bool operator==(const BankAccount& other);

};

std::ostream& operator<<(std::ostream& stream, const BankAccount& in);

#endif //PROG2_NHF_BANKACCOUNT_HPP
