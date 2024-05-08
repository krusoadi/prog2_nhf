#include "../headers/Currency.h"

const std::string Currency::symbols[] =  {"Eur", "Ft", "$"};

double Currency::valueToEUR[] = {1, 350, 400};

double Currency::randomValue(double low, double high) {

    // Safe C++ 11 random double generator

    std::random_device randomizer;
    std::default_random_engine randEng(randomizer());
    std::uniform_real_distribution<double> bound(low,high);
    return bound(randEng);
}

void Currency::updateCurrency() {
    valueToEUR[EUR] = 1;
    for (int i = 1; i < END; i++) { // EUR does not need to be updated.
        valueToEUR[i] = randomValue(LOW_BOUNDS[i], UPPER_BOUNDS[i]);
    }
}

void Currency::printCurrency() {
    std::cout << "From EUR:\tHUF:" << Currency::valueToEUR[HUF] << "\tUSD:" << Currency::valueToEUR[USD] << std::endl;
}
