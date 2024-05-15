#ifndef PROG2_NHF_UI_HPP
#define PROG2_NHF_UI_HPP
#include <string>
#include <iostream>

class UI {
private: // Private Static variables, functions

    // Static Const Strings

    static const std::string welcomeText;
    static const std::string menuText;

    static const std::string shareMenuText;
    static const std::string workerMenuText;

    static const std::string accountTextMenu;
    static const std::string loginMenu;
    static const std::string username;
    static const std::string password;

    static const std::string logOut;
    static const std::string goodbye;

    static const std::string IllegalNumber;

    // Static variables

    static bool runtime;

    // Static Functions

    static void print(const std::string& text);
    static void wrongInput();

private: // Private variables (object related)
    int indexIn; // Given menuIndex
    bool is_loggedIn; // Flag if the user is logged in

private:
    void AccountUI();
    void logIn();
    void makeAcc();
    void exit();
public:
    UI();
    [[nodiscard]] int getIndexIn() const;
    void mainLoop();
};


#endif //PROG2_NHF_UI_HPP
