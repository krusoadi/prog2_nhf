#ifndef PROG2_NHF_BANKACCOUNT_HPP
#define PROG2_NHF_BANKACCOUNT_HPP

#include "Share.hpp"
#include "TContainer.hpp"

class BankAccount {
private:
    // Data of the user

    IDManager ID; // Bank account ID (for user verification in FileManager)
    std::string name; // Users Full name
    bool isMale; // Users Gender
    Money userMoney; // Users amount of money
    bool isWorker; // Is the user a worker (admin)

    TContainer<OwnedShare> userShares; // Bought shares of the user stored in a TContainer

public:
    // Constructors/Destructors

    BankAccount(); //All of the constructors are needed
    explicit BankAccount(IDManager id);
    BankAccount(const Money &money, std::string name, bool isMale, bool isWorker);
    BankAccount(const BankAccount &other);

    ~BankAccount() = default;

    // Getters

    [[nodiscard]] Money getMoney() const;
    [[nodiscard]] unsigned int getId() const;
    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] std::string getGender() const;
    [[maybe_unused]] [[nodiscard]] bool getIsWorker() const;
    [[nodiscard]] bool getIsMale() const;
    [[nodiscard]] const TContainer<OwnedShare> &getUserShares() const;

    // Setters TODO check if they are needed

    [[maybe_unused]] void setMoney(const Money &in);
    [[maybe_unused]] void setName(const std::string &name);
    [[maybe_unused]] void setIsWorker(bool isWorkerIn);

    // Money managing methods

    void addMoney(const Money &in);
    void subtractMoney(const Money &in);

    // Share managing functions

    void BuyShares(Share &SType, int amount);
    void SellShares(Share &SType, int amount);

    // Share printer (Debug purposes) TODO check if needed.

    void revealShares();

    // Operators

    bool operator==(const BankAccount &other);

    // Loads the Owned Shares of the account
    void loadOShares(const OwnedShare &in);
};

std::ostream &operator<<(std::ostream &stream, const BankAccount &in);

#endif //PROG2_NHF_BANKACCOUNT_HPP
