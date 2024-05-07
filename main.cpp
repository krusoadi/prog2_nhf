#include <iostream>
#include "BankAccount.h"


int main() {

    Money temp = {10, EUR};
    BankAccount tempAcc = {temp, "Krusoadi", true};


    std::cout << tempAcc << std::endl;

    tempAcc.setName("Teszter Janos");

    tempAcc.setMoney(temp.convertCurrency(HUF));

    tempAcc.addMoney(temp);

    std::cout << tempAcc << std::endl;

    return 0;
}
