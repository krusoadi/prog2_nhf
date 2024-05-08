#include <iostream>
#include "BankAccount.hpp"


int main() {

    Share testShare("Apple Inc.", Money(2000, HUF), 100);

    Money temp = {10, EUR};

    BankAccount tempAcc = {temp, "Krusoadi", true, true};


    std::cout << tempAcc << std::endl;

    tempAcc.setName("Teszter Janos");

    std::cout << testShare << std::endl;

    tempAcc.BuyShares(testShare, 10);

    std::cout << "\n";

    OwnedShare tempOwnSh = tempAcc.getIndex(0);
    tempAcc.addMoney(temp);

    std::cout << testShare << std::endl;

    std::cout << tempOwnSh << std::endl;

    std::cout << "\n";

    tempAcc.SellShares(testShare, 5);

    std::cout << testShare << std::endl;

    tempOwnSh = tempAcc.getIndex(0);

    std::cout << tempOwnSh << std::endl;

    tempAcc.SellShares(testShare, 5);

    std::cout << tempAcc << std::endl;

    std::cout << testShare << std::endl;

    return 0;
}
