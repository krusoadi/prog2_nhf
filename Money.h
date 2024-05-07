
#ifndef PROG2_NHF_MONEY_H
#define PROG2_NHF_MONEY_H

enum BankMoneyTypes {
    EUR,
    HUF,
    USD,
};

double vals[3] = {1, 355, 0.77};

class Money {
    double value;
    BankMoneyTypes currency;
public:

    // Constructors

    Money(double value, BankMoneyTypes currency);
    Money();

    // Getters

    double getValue() const;
    BankMoneyTypes getCurrency() const;

    // Setters

    void setCurrency(BankMoneyTypes cur);
    void setValue(double val);

    // Converters

    Money convertCurrency(BankMoneyTypes dest) const;

    // Operators

    Money operator+(const Money& other);
    Money operator*(double rate);

};


#endif //PROG2_NHF_MONEY_H
