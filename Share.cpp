#include "Share.h"
#include <utility>
#include <random>

Share::Share(std::string name, const Money &value, unsigned int available) : name(std::move(name)), value(value),
                                                                                    available(available) {}

double Share::getNewRate(bool decrease) {

    // Safe C++ 11 random generator

    std::random_device randomizer;
    std::mt19937 gen(randomizer());

    int a, b;

    decrease ? a = 80 : a = 101 ;
    decrease ?  b = 100 : b = 135;

    std::uniform_int_distribution<>dis(a,b);

    return ((double)dis(gen)) / 100;
}

void Share::calculateNewPrice(int sold) {
    double rate = getNewRate(sold);
    this->value *= rate;
}

void Share::sell(int n) {
    this->available += n;
    calculateNewPrice(true);
}

bool Share::buy(int n) {
    if (this->available >= n) {
        this->available -= n;
        calculateNewPrice(false);
        return true;
    }
    return false;
}


