#ifndef PROG2_NHF_CURRENCY_H
#define PROG2_NHF_CURRENCY_H
#include <random>
#include <string>
#include <iostream>
#define END 3 // max tombertek a valutakra

enum CurrencyTypes {
    EUR,
    HUF,
    USD,
};

class Currency {
private:
    static constexpr double LOW_BOUNDS[END] = {1, 300, 0.50};
    static constexpr double UPPER_BOUNDS[END] = {1, 450, 1.25};
    static double randomValue(double low, double high);

public:
    //Static Value of Currency (based on EURO)

    static double valueToEUR[END];
    static const std::string symbols[3];

    static void updateCurrency();
    static void printCurrency();
};


#endif //PROG2_NHF_CURRENCY_H
