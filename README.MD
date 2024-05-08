# Basics of Programming II. Homework
## Introduction

## Classes

### [Money](headers/Money.hpp)

This class is a data structure for money basically, the main reasons for
creating this class were currencies and transfers. Defining operators was
essential, due to different currencies.

### [Share](headers/Share.hpp)

The Share class defines everything about a specified share, the price, the number of
available shares and the name of the share. With every buy, and sell, the price changes.

> [!IMPORTANT]
>This class is only used for storing information about the share, accounts use OwnedShare.

### [OwnedShare](headers/Share.hpp)

These are the shares, that a user can obtain. The object only stores the number of bought shares, and a pointer
to its Share object. Every detail about the share is stored in the Master object, to keep up-to-date prices and 
available shares.

### [BankAccount](headers/BankAccount.hpp)

This class stores data, about users, with a generated ID. 
