#include "headers/memtrace.h"
#include "headers/BankAccount.hpp"
#include "headers/UI.hpp"

int main() {
    BankSystem system(Money(15000, EUR));

    FileManager manager("files\\test.txt", "files\\test2.txt", "files\\test3.txt");
    UI main(system, manager);
    main.boot();
    return 0;
}