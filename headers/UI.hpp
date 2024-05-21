#ifndef PROG2_NHF_UI_HPP
#define PROG2_NHF_UI_HPP

#include <iomanip>
#include <string>
#include <iostream>
#include <conio.h> // for safe password staring
#include "BankSystem.hpp"
#include "FileManager.hpp"

#define ENTER 13

class UI {
private: // Private Static variables, functions

    // Static Const Strings, which needs to be stored, in the program

    static const std::string welcomeText;
    static const std::string menuText;

    static const std::string shareMenuText;

    static const std::string accountTextMenu;
    static const std::string usernameTXT;
    static const std::string passwordTXT;

    static const std::string goodbye;

    static const std::string IllegalNumber;

    // Static variables

    static bool runtime; // Main flag for runtime

    // Static Functions

    static void print(const std::string &text); // Prints out a string (for convention)
    static void wrongMenuPoint(); // Restores the IO when wrong input was given
    static std::string safeInput(); // for passwords, it stars out the input;
    static std::string hashStr(const std::string &in); // Hashing function (really primitive hash)
    static bool hasDigit(const std::string& in); // Checks if a string has digits in it
    static void clearScreen(); // Clears the screen
    static bool checkAnswerFail(); // Checks the input if it has any errors //TODO
    static void wrongInput(); // Restores input if a bad answer came //TODO

private: //Private variables (user related)
    int indexIn; // Given menuIndex
    bool is_loggedIn; // Flag if the user is logged in
    User thisUser; // The current users data stored here too, but needs to be refreshed always

private: // Private variables (object related)
    BankSystem system; // The system where the banks data stored
    FileManager manager; // The IO manager class.

private: // Object related private methods
    void AccountUI(); // Login/Register selector
    void logIn(); // Login panel
    void makeAcc(); // Register [register keyword is reserved]
    void exit(); // Exit function
    void depositMoney(); // Money deposit function
    void withdrawMoney();// Money withdraw function
    void refreshUser(); // Loads changes to our user.
    void myAccount(); // Prints info about the users account
    void mainMenuFunctions(); // Switch case of the menu
    void ShareMenu(); // Opens the share menu and prints the dialog
    void ShareMenuFunctions(); // Redirects to the functions of the Share menu
    void printBankShares(); // Prints out the values of each share.
    void buyShares(); // Interface for buying shares
    void sellShares(); // Interface for selling shares
    void convertMyCurrency(); // Converts the users currency
    void showMyShares(); // Prints out the current users shares, with values
public:
    UI(const BankSystem &systemIn, const FileManager &managerIn); // Only constructor needed
    ~UI(); // We need the destructor, because with every quit we save the data.
    void mainLoop(); // Main menus loop.
    void boot();
};


#endif //PROG2_NHF_UI_HPP
