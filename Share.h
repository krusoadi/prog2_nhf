
#ifndef PROG2_NHF_SHARE_H
#define PROG2_NHF_SHARE_H

#include "Money.h"
#include <string>

class Share {
private:
    std::string name;
    Money value;
    unsigned int available;

    double static getNewRate(bool decrease);
    void calculateNewPrice(int change);

public:
    Share(std::string name, const Money &value, unsigned int available);

    void sell(int n);
    bool buy(int n);

};


#endif //PROG2_NHF_SHARE_H
