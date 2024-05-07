#ifndef PROG2_NHF_BANKACCOUNT_H
#define PROG2_NHF_BANKACCOUNT_H

enum BankMoneyTypes {
    EUR,
    HUF,
    USD,
};



class BankAccount {
private:
    const unsigned int ID;
    double money;
    BankMoneyTypes currency;
public:

    // Constructors/Destructors

    BankAccount();
    BankAccount(double amount, BankMoneyTypes curr);
    BankAccount(const BankAccount& other);
    ~BankAccount() = default;

    // Getters

    double getMoney() const;
    BankMoneyTypes getCurrency() const;
    unsigned int getId() const;


    // Setters

    void setMoney(double money);
    void setCurrency(BankMoneyTypes currency);

    // Static functions

    static int generateID();

    // Operator overloads

    void operator+(const BankAccount& other);

};


#endif //PROG2_NHF_BANKACCOUNT_H
