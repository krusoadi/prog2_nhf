#include "../headers/Currency.h"

const std::string Currency::symbols[] =  {"Eur", "Ft", "$"};

double Currency::randomValue(double low, double high) {

    // Safe C++ 11 random double generator

    std::random_device randomizer;
    std::default_random_engine randEng(randomizer());
    std::uniform_real_distribution<double> bound(low,high);
    return bound(randEng);
}

void Currency::updateCurrency() {
    valuetoEUR[EUR] = 1;
    for (int i = 1; i < END; i++) { // EUR does not need to be updated.
        valuetoEUR[i] = randomValue(LOW_BOUNDS[i], UPPER_BOUNDS[i]);
    }
}