#ifndef PROG2_NHF_CURRENCY_H
#define PROG2_NHF_CURRENCY_H
#include <random>

// TODO implementalni, a bankba es itt is

#define END 3 // max tombertek a valutakra

enum BankMoneyTypes {
    EUR,
    HUF,
    USD,
};

inline const double LOW_BOUNDS[END] = {1, 300, 0.50};
inline const double UPPER_BOUNDS[END] = {1, 450, 1.25};

class Currency {
private:
    double valuetoEUR[END] ={1}; // alapveto eurohoz kepest mert ar

    static double randomValue(double low, double high);
public:
    void updateCurrency();
    double getValue(BankMoneyTypes curr);

};


#endif //PROG2_NHF_CURRENCY_H
