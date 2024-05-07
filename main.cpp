#include <iostream>
#include "BankAccount.h"


int main() {

    Money temp = {10, EUR};
    BankAccount tempAcc = {temp};
    tempAcc.setName("Teszter Janos");

    std::cout << tempAcc << std::endl;

    tempAcc.setMoney(temp.convertCurrency(HUF));

    std::cout << tempAcc << std::endl;

    return 0;
}
