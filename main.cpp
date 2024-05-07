#include <iostream>
#include "BankAccount.h"


int main() {

    Share testShare("Tesztadat", Money(2000, HUF), 100);

    Money temp = {10, EUR};

    BankAccount tempAcc = {temp, "Krusoadi", true, true};


    std::cout << tempAcc << std::endl;

    tempAcc.setName("Teszter Janos");
    tempAcc.BuyShares(testShare, 10);

    tempAcc.setMoney(temp.convertCurrency(HUF));

    OwnedShare tempOwnSh = tempAcc.getIndex(0);
    tempAcc.addMoney(temp);

    std::cout << tempOwnSh.showValue() << std::endl;

    std::cout << tempOwnSh.getAmount() << std::endl;
    std::cout << tempOwnSh.showName() << std::endl;
    std::cout << tempOwnSh.getMaster() << std::endl;
    std::cout << &testShare << std::endl;


    tempAcc.SellShares(testShare, 5);

    tempOwnSh = tempAcc.getIndex(0);

    std::cout << tempOwnSh.showValue() << std::endl;

    std::cout << tempOwnSh.getAmount() << std::endl;
    std::cout << tempOwnSh.showName() << std::endl;

    tempAcc.SellShares(testShare, 5);


    std::cout << tempAcc << std::endl;

    return 0;
}
