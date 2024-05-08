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

    // Bounds (used by randomValue) and the random generator for currency

    static constexpr double LOW_BOUNDS[END] = {1, 350, 0.50};
    static constexpr double UPPER_BOUNDS[END] = {1, 400, 1};
    static double randomValue(double low, double high);

public:
    //Static Value of Currency (based on EURO)

    static double valueToEUR[END];
    static const std::string symbols[3];

    static void updateCurrency();
    static void printCurrency();
};


#endif //PROG2_NHF_CURRENCY_H
