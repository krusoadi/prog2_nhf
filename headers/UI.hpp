#ifndef PROG2_NHF_UI_HPP
#define PROG2_NHF_UI_HPP

#include <string>
#include <iostream>
#include <conio.h> // for safe password staring
#include "BankSystem.hpp"
#include "FileManager.hpp"

#define ENTER 13

class UI {
private: // Private Static variables, functions

    // Static Const Strings

    static const std::string welcomeText;
    static const std::string menuText;

    static const std::string shareMenuText;
    static const std::string workerMenuText;

    static const std::string accountTextMenu;
    static const std::string loginMenu;
    static const std::string usernameTXT;
    static const std::string passwordTXT;

    static const std::string logOut;
    static const std::string goodbye;

    static const std::string IllegalNumber;

    // Static variables

    static bool runtime;

    // Static Functions

    static void print(const std::string &text);

    static void wrongInput();

    static std::string safeInput(); // for passwords, it stars out the input;
    static std::string
    hashStr(const std::string &in); // NOT SAFE hash, just for not storing the passwords as they are :)

private: //Private variables (user related)
    int indexIn; // Given menuIndex
    bool is_loggedIn; // Flag if the user is logged in
    User thisUser;

private: // Private variables (object related)
    BankSystem system;
    FileManager manager;

private:
    void AccountUI(); // Login/Register selector
    void logIn(); // Login panel
    void makeAcc(); // Register [register keyword is reserved]
    void exit(); // Exit function
    void depositMoney();
    void withdrawMoney();
    void refreshUser();
    void myAccount();
    void mainMenuFunctions();

public:
    UI(const BankSystem &systemIn, const FileManager &managerIn);
    ~UI();
    void mainLoop();
};


#endif //PROG2_NHF_UI_HPP
