#include "../headers/Money.hpp"

Money::Money(double value, CurrencyTypes currency) : value(value), moneyCurr(currency) {}

Money::Money(): value(0), moneyCurr(EUR) {}

Money Money::TransferCurrency(CurrencyTypes our, const Money &other) {
    double returnValue;

    if (our != other.moneyCurr) {
        returnValue = (other.value / Currency::valueToEUR[other.moneyCurr]) * Currency::valueToEUR[our];

        return {returnValue, our};
    }
    return other;
}

double Money::getValue() const {
    return value;
}

CurrencyTypes Money::getCurrency() const {
    return moneyCurr;
}

[[maybe_unused]] void Money::setCurrency(CurrencyTypes cur) {
    this->moneyCurr = cur;
}

[[maybe_unused]] void Money::setValue(double val) {
    this->value = val;
}

[[maybe_unused]] Money Money::convertCurrency(CurrencyTypes dest) const { // Alapvetoen EUR ba van minten, oda valt vissza es at a masikba
    return Money::TransferCurrency(dest, *this);
}

Money Money::operator+(const Money &other) {
    Money temp = Money::TransferCurrency(this->moneyCurr, other);
    return {this->value+ temp.value, this->moneyCurr};

}
Money Money::operator-(const Money &other) {
    Money temp = Money::TransferCurrency(this->moneyCurr, other);
    return {this->value - temp.value, this->moneyCurr};
}

Money Money::operator*(double rate) {
    if (rate < 0) {
        throw Exceptions(NegativeMoney, "Tried to multiply money with negative amount.");
    }
    return {this->value * rate, this->moneyCurr};
}

Money &Money::operator+=(const Money &other) {
    Money temp = Money::TransferCurrency(this->moneyCurr, other);
    this->value += temp.value;
    return *this;
}

Money &Money::operator-=(const Money &other) {
    Money temp = Money::TransferCurrency(this->moneyCurr, other);
    this->value -= temp.value;
    return *this;
}

Money &Money::operator*=(double rate) {
    if (rate < 0) {
        throw Exceptions(NegativeMoney, "Tried to multiply money with negative double amount.");
    }
    this->value *= rate;

    return *this;
}

Money Money::operator*(int amount) {
    if (amount < 0) {
        throw Exceptions(NegativeMoney, "Tried to multiply money with negative int amount.");
    }
    return {this->value * amount, this->moneyCurr};
}

bool Money::operator==(const Money &other) {
    Money temp = Money::TransferCurrency(this->moneyCurr, other);

    return this->value == temp.value;
}

bool Money::operator<(const Money &other) {
    Money temp = Money::TransferCurrency(this->moneyCurr, other);

    return this->value < temp.value;
}

bool Money::operator>(const Money &other) {
    Money temp = Money::TransferCurrency(this->moneyCurr, other);

    return this->value > temp.value;
}

std::ostream& operator<<(std::ostream& stream, const Money& in) {
    stream << in.getValue() << " " << Currency::SYMBOLS[in.getCurrency()];
    return stream;
}