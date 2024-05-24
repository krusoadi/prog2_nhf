# Basics of Programming II. Homework

## Introduction

This project is my homework for my Programming II. course.

## Classes

### [TContainer](headers/TContainer.hpp)

Most of the project were not allowed to use
the [Standard Template Library](https://www.geeksforgeeks.org/the-c-standard-template-library-stl/),
so I needed to write an own template storage class, which is TContainer.
It's a Normal template class with a dynamic array, made to mimic
the [std::vector](https://en.cppreference.com/w/cpp/container/vector).
Unfortunately it's not as (and never meant to be) optimal as an STL container, it works for this project perfectly.
Lately I've made a ConstIterator and an Iterator for the Container, which work perfectly.

### [Currency](headers/Currency.hpp)

The Currency class is fully static, its main purpose is to make currency modifiable
and random. It stores the currency SYMBOLS too.

### [Money](headers/Money.hpp)

This class is a data structure for money basically, the main reasons for
creating this class were currencies and transfers. Defining operators was
essential, due to different currencies.

### [Share](headers/Share.hpp)

The Share class defines everything about a specified share, the price, the number of
available shares and the name of the share. With every buy, and sell, the price changes.

> [!IMPORTANT]
> This class is only used for storing information about the share, accounts use OwnedShare.

### [OwnedShare](headers/Share.hpp)

These are the shares, that a user can obtain. The object only stores the number of bought shares, and the ID
of its Share object. Every detail about the share is stored in the Master object, to keep up-to-date prices and
available shares.

### [BankAccount](headers/BankAccount.hpp)

This class stores data, about users, with a generated ID. The users can buy shares, deposit etc, except login data,
because I've made a [user](headers/User.hpp) class for that.

### [IDManager](headers/IDManager.hpp)

IDManagers main use is in the Shares and BankAccounts. It generates a new ID which isn't reserved by anything in the 
programs current state. Main reason of this class is to avoid ID collision during runtime, because that would cause
problems when handling Shares and OwnedShares.


### [User](headers/User.hpp)

The User class encapsulates the BankAccounts and the login data of a user. The main reasons for this are the admin
functions (not yet made), which will be able to modify most of the users data.

### [FileManager](headers/FileManager.hpp)

The FileManager class handles all file I/O for loading or saving data which includes the users data, the accounts data
and the shares data.

### [BankSystem](headers/BankSystem.hpp)

The BankSystem class stores all the data which is needed for the program to operate. Users, accounts and shares data are
stored here, it functions just like a bank.

### [UI](headers/UI.hpp)

The UI handles all user interactions, through the console, and handles input errors etc.






