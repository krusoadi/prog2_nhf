#include <iostream>
#include "BankAccount.h"


int main() {

    Money temp = {10, EUR};
    BankAccount tempAcc = {temp, "Krusoadi"};


    std::cout << tempAcc << std::endl;

    tempAcc.setName("Teszter Janos");

    tempAcc.setMoney(temp.convertCurrency(HUF));

    std::cout << tempAcc << std::endl;

    return 0;
}
