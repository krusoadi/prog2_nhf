#include "../headers/Money.hpp"

Money::Money(double value, BankMoneyTypes currency) : value(value), currency(currency) {}

Money::Money(): value(0), currency(EUR) {}

Money Money::TransferCurrency(BankMoneyTypes ours, const Money &other) {
    double retval;

    if (ours != other.currency) {
        retval = (other.value / vals[other.currency]) *vals[ours];

        return {retval, ours};
    }
    return other;
}

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
    return Money::TransferCurrency(dest, *this);
}

Money Money::operator+(const Money &other) {
    Money temp = Money::TransferCurrency(this->currency, other);
    return {this->value+ temp.value, this->currency};

}
Money Money::operator-(const Money &other) {
    Money temp = Money::TransferCurrency(this->currency, other);
    return {this->value - temp.value, this->currency};
}

Money Money::operator*(double rate) {
    if (rate < 0) {
        throw Exceptions(NegativeMoney, "Tried to multiply money with negative amount.");
    }
    return {this->value * rate, this->currency};
}

Money &Money::operator+=(const Money &other) {
    Money temp = Money::TransferCurrency(this->currency, other);
    this->value += temp.value;
    return *this;
}

Money &Money::operator-=(const Money &other) {
    Money temp = Money::TransferCurrency(this->currency, other);
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
    return {this->value * amount, this->currency};
}

bool Money::operator==(const Money &other) {
    Money temp = Money::TransferCurrency(this->currency, other);

    return this->value == temp.value;
}

bool Money::operator<(const Money &other) {
    Money temp = Money::TransferCurrency(this->currency, other);

    return this->value < temp.value;
}

bool Money::operator>(const Money &other) {
    Money temp = Money::TransferCurrency(this->currency, other);

    return this->value > temp.value;
}

std::ostream& operator<<(std::ostream& stream, const Money& in) {
    stream << in.getValue() << " " << symbols[in.getCurrency()];
    return stream;
}