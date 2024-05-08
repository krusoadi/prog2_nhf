#include "../headers/Currency.h"

double Currency::randomValue(double low, double high) {

    // Safe C++ 11 random double generator

    std::random_device randomizer;
    std::default_random_engine randEng(randomizer());
    std::uniform_real_distribution<double> bound(low,high);
    return bound(randEng);
}

void Currency::updateCurrency() {
    for (int i = 0; i < END; ++i) {
        valuetoEUR[i] = randomValue(LOW_BOUNDS[i], UPPER_BOUNDS[i]);
    }
}

double Currency::getValue(BankMoneyTypes curr) {
    return valuetoEUR[curr];
}
