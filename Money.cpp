#include "Money.h"

Money::Money(double value, BankMoneyTypes currency) : value(value), currency(currency) {}

Money::Money(): value(0), currency(EUR) {}


double Money::getValue() const {
    return value;
}

BankMoneyTypes Money::getCurrency() const {
    return currency;
}

void Money::setCurrency(BankMoneyTypes cur) {
    this->currency = cur;
}

void Money::setValue(double val) {
    this->value = val;
}

Money Money::convertCurrency(BankMoneyTypes dest) const { // Alapvetoen EUR ba van minten, oda valt vissza es at a masikba
    double tempValue = this->value / vals[this->currency];
    return {tempValue * vals[dest], dest};
}

Money Money::operator+(const Money &other) {
    if (this->currency == other.currency) {
        return {this->value+other.value, this->currency};
    }

    Money temp = other.convertCurrency(this->currency);

    return {this->value + temp.value, this->currency};
}

Money Money::operator*(double rate) {
    if (rate < 0) {
        // TODO EXCEPTION
    }
    return {this->value * rate, this->currency};
}
