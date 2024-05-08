#ifndef PROG2_NHF_MONEY_HPP
#define PROG2_NHF_MONEY_HPP

#include <iostream>
#include "Exceptions.hpp"
#include "Currency.h"

class Money {
    double value;
    CurrencyTypes moneyCurr; // acronym for Money Currency

    // Static Private currency converter

    static Money TransferCurrency(CurrencyTypes our, const Money& other);

public:

    // Constructors, Destructors

    Money(double value, CurrencyTypes currency);
    Money();

    ~Money() = default;

    // Getters

    [[nodiscard]] double getValue() const;
    [[nodiscard]] CurrencyTypes getCurrency() const;

    // Setters

    void setCurrency(CurrencyTypes cur);
    void setValue(double val);

    // Converters (for object)

    [[nodiscard]] Money convertCurrency(CurrencyTypes dest) const;

    // Arithmetic Operators

    Money operator+(const Money& other);
    Money operator-(const Money& other);
    Money operator*(double rate);
    Money operator*(int amount);

    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);
    Money& operator*=(double rate);

    // Compare operators

    bool operator==(const Money& other);
    bool operator<(const Money& other);
    bool operator>(const Money& other);
};

std::ostream& operator<<(std::ostream& stream, const Money& in);


#endif //PROG2_NHF_MONEY_HPP
