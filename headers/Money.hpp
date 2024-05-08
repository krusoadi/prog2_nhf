#ifndef PROG2_NHF_MONEY_HPP
#define PROG2_NHF_MONEY_HPP

#include <iostream>
#include "Exceptions.hpp"
#include "Currency.h"

class Money {
    double value;
    CurrencyTypes moneyCurr; // Rovidites fontos

    // Static Private moneyCurr converter

    static Money TransferCurrency(CurrencyTypes our, const Money& other);

public:

    // Constructors

    Money(double value, CurrencyTypes currency);
    Money();

    // Getters

    double getValue() const;
    CurrencyTypes getCurrency() const;

    // Setters

    void setCurrency(CurrencyTypes cur);
    void setValue(double val);

    // Converters (for object)

    Money convertCurrency(CurrencyTypes dest) const;

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
