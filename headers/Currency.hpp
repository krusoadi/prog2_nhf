#ifndef PROG2_NHF_CURRENCY_HPP
#define PROG2_NHF_CURRENCY_HPP

#include <random>
#include <string>
#include <iostream>
#include "memtrace.h"

#define END 3 // Max number of currencies

enum CurrencyTypes {
    EUR,
    HUF,
    USD,
};

class Currency {
private:
    // Bounds (used by randomValue)

    static constexpr double LOWER_BOUNDS[END] = {1, 350, 0.50}; // Lower bounds of random generations
    static constexpr double UPPER_BOUNDS[END] = {1, 400, 1}; // Upper bounds of random generations

    // Random new currency generator
    static double randomValue(double low, double high);

public:
    //Static Value of Currency (based on EURO)
    static double valueToEUR[END];

    // Static variables for Currency symbols
    static const std::string SYMBOLS[3];

    // Static methods for updating and printing the currencies
    static void updateCurrency();

    // Prints out currency value
    static void printCurrency();
};

#endif //PROG2_NHF_CURRENCY_HPP
