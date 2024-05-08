#ifndef PROG2_NHF_MONEY_HPP
#define PROG2_NHF_MONEY_HPP

#include <iostream>
#include "Exceptions.hpp"
enum BankMoneyTypes {
    EUR,
    HUF,
    USD,
};

inline double vals[3] = {1, 355, 0.77};
inline const char* symbols[3] = {"Eur", "Ft", "$"};


class Money {
    double value;
    BankMoneyTypes currency;

    static Money temporaryCurrency(BankMoneyTypes ours,const Money& other); // kodismetles ellen, megnezi a masik penztipousat es atvaltja a mienkbe
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

    Money convertCurrency(BankMoneyTypes dest) const; // ez u.a mint a privat, csak ez nem statikus, objektumhoz kotott

    // Operators

    Money operator+(const Money& other);
    Money operator-(const Money& other);
    Money operator*(double rate);
    Money operator*(int amount);

    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);
    Money& operator*=(double rate);

    bool operator==(const Money& other);
    bool operator<(const Money& other);
    bool operator>(const Money& other);
};

std::ostream& operator<<(std::ostream& stream, const Money& in);


#endif //PROG2_NHF_MONEY_HPP
