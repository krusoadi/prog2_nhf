#include <iostream>
#include "headers/BankAccount.hpp"
#include "headers/UI.hpp"
int main() {
    BankSystem system(Money(15000, EUR));
    FileManager manager("..\\files\\test.txt", "..\\files\\test2.txt", "..\\files\\test3.txt");

    try {
        auto temp = manager.loadUsers();
        system.loadUsers(temp);
    }
    catch (const Exceptions &e) {
        std::cerr << e.what();
        if (e.getType() == FileError) {
            std::cerr << "File could not be opened.\n" << std::endl;
        }
    }

    UI(system, manager).mainLoop();
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