#include <iostream>
#include "headers/BankAccount.hpp"
#include "prototype_containers/TContainer.hpp"

// Tested: add_back, add_front, pop_front, pop_back, pop_index, add_index, getNum, isEmpty, Constructors (all of them)
// Need to check if the program leaks memory
int main() {
    Currency::updateCurrency();

    TContainer<Money> temp;
    for (int i = 0; i < 15; i++) {
        temp.add_back(Money(i, EUR));
    }

    auto max = temp.getNum();

    TContainer<Money> test2;

    for (int i = 0; i < max; i++) {
        test2.add_back(temp[i].convertCurrency(HUF));
    }

    test2.clear();

    std::cout << temp << std::endl;
    std::cout << test2 << std::endl;
    return 0;
}



/*
Currency::updateCurrency();

Currency::printCurrency();

Share testShare("Apple Inc.", Money(2000, HUF), 100);
Share testShare2("Tesla", Money(1500, HUF), 50);

Money temp = {1000, EUR};

BankAccount tempAcc = {temp, "Krusoczki Adam", true, true};

std::cout << tempAcc << std::endl;

std::cout<<"\n";

std::cout << testShare << std::endl;
std::cout << testShare2 << std::endl;

tempAcc.BuyShares(testShare, 10);
tempAcc.BuyShares(testShare2, 10);

std::cout << "\nBought Shares..\n";

std::cout << tempAcc << std::endl;

std::cout<<"\n";

std::cout << testShare << std::endl;
std::cout << testShare2 << std::endl;

std::cout<<"\n";

tempAcc.revealShares();


std::cout << "\nSold Apple Shares...\n";

tempAcc.SellShares(testShare, 5);


std::cout << tempAcc << std::endl;

std::cout<<"\n";

std::cout << testShare << std::endl;
std::cout << testShare2 << std::endl;

std::cout<<"\n";

tempAcc.revealShares();

std::cout << "\nSold Tesla Shares...\n";

tempAcc.SellShares(testShare2, 5);

std::cout << tempAcc << std::endl;

std::cout<<"\n";

std::cout << testShare << std::endl;
std::cout << testShare2 << std::endl;

std::cout<<"\n";

tempAcc.revealShares();
*/