#include <utility>

#include "../headers/UI.hpp"

bool UI::runtime = true;

const std::string UI::welcomeText = "Welcome To NewVille Bank, this program is made by Adam Krusoczki"
                                    "My github link is www.github.com/krusoadi\n\n";

const std::string UI::menuText = "Please type in your selected menu point. Options:\n\n"
                                 "1. Deposit Money\n"
                                 "2. Withdraw Money\n"
                                 "3. Check my account\n"
                                 "4. Shares\n"
                                 "5. View Currency\n"
                                 "6. Log out\n";

const std::string UI::shareMenuText = "Please type in your selected menu point. Options:\n\n"
                                      "1. Show information about the shares\n"
                                      "2. Buy shares\n"
                                      "3. Sell shares\n"
                                      "4. Show my shares\n"
                                      "5. Return\n";

const std::string UI::workerMenuText = "Please type in your selected menu point. Options:\n\n"
                                       "1. Banks Finances\n"
                                       "2. Manage Shares.\n"
                                       "3. Manage Users\n"
                                       "4. Manage Currency\n"
                                       "5. Log out\n";

const std::string UI::accountTextMenu = "Please type in your selected menu point. Options:\n\n"
                                        "1. Login\n"
                                        "2. Register\n"
                                        "3. Exit\n";

const std::string UI::loginMenu = "You will need a name and password to log in."
                                  "Press any key if you are ready!\n";

const std::string UI::username = "\nUsername >";

const std::string UI::password = "\nPassword >";

const std::string UI::logOut = "\nAre you sure you want to log out? (y/n)\n";

const std::string UI::goodbye = "\nThank you for using this app, have a nice day! Goodbye!\n";

const std::string UI::IllegalNumber = "\nThe menu point you gave is not defined. Please retry\n";

void UI::print(const std::string &text) {
    std::cout << text << std::endl;
}

void UI::wrongInput() {
    fflush(stdin);
    std::cin.clear();
    print(IllegalNumber);
}

void UI::mainLoop() {
    AccountUI();
    if (!this->is_loggedIn) {
        UI::runtime = false;
    }

    while (UI::runtime) {
        print(UI::menuText);
        std::cin >> indexIn;

        if (indexIn == 6) {
            exit();
        }

    };

}

UI::UI(const BankSystem &systemIn, const FileManager &managerIn) : indexIn(0), is_loggedIn(false),
                                                                   manager(managerIn), system(systemIn) {
    print(UI::welcomeText);
}

void UI::AccountUI() {
    while (!is_loggedIn) {
        print(UI::accountTextMenu);
        std::cin >> this->indexIn;


        switch (indexIn) {
            case 1:
                logIn();
                break;
            case 2:
                makeAcc();
                break;
            case 3:
                exit();
                return;
            default:
                wrongInput();
                break;
        }
    }
}

void UI::logIn() { // TODO finish if needed
    std::string userName;
    std::string Password;

    print("\nType in your selected username:");

    std::cin >> userName;
    print("\n Type in your password");
    if (!system.isUserNameReserved(userName)) {
        print("There is no account with this username, please try again!");
        return;
    }

    Password = safeInput();
    std::string hashed = hashStr(Password);
    try {
        const User &found = system.searchByUserName(userName);
        if (!found.MatchPassword(hashed)) {
            print("Incorrect password, try again!");
            return;
        }
        print("Successfully logged in! Welcome back!");
        this->is_loggedIn = true;
    } catch (const Exceptions &e) {
        std::cerr << e.what();
        this->is_loggedIn = false;

    }

}

void UI::makeAcc() {
    User newUser;
    std::string newUserName;
    std::string newPassword;
    std::string name;

    print("\nType in your selected username:");
    std::cin >> newUserName;
    if (system.isUserNameReserved(newUserName)) {
        print("Username is already in use please choose an other one.");
        return;
    }

    print("\n Type in your password");
    newPassword = safeInput();
    print("\nType in your first name:");
    std::cin >> name;
    print("\nType in your last name:");
    std::string last;
    std::cin >> last;
    name += " " + last;

    newUser.setUsername(newUserName);
    newUser.setHashedPw(hashStr(newPassword));
    newUser.setUserBank(BankAccount(Money(0, EUR), name, false, true));
    system.addNewUser(newUser);
    manager.saveUsers(system.getUsers());

    print("Congratulations, you've just made your first account.");
    this->is_loggedIn = true;
}

void UI::exit() {
    UI::runtime = false;
    this->is_loggedIn = false;
    print(UI::goodbye);
}

std::string UI::safeInput() {
    std::string buffer; // full password
    char tch; // temp character

    while ((tch = static_cast<char>(_getch())) != ENTER) {
        if (tch != '\b') { // Checks if the char was a backspace
            std::cout << '*';
            buffer += tch;
        } else {
            if (!buffer.empty()) {
                std::cout << "\b \b"; // Erasing '*', and moving the cursor back
                buffer.erase(buffer.length() - 1);
            }
        }
    }
    print(""); // flush & newline
    return buffer;
}

std::string
UI::hashStr(const std::string &in) { // The only point of this function is to not store the passwords as they are.
    unsigned long long hashNumber = 5311;

    for (int i = 0; i < 3; ++i) {
        for (char tch: in) {
            hashNumber = ((hashNumber << 5) + hashNumber) + tch;
        }
    }
    return std::to_string(hashNumber);
}


