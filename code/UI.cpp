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

void UI::print(const std::string& text) {
    std::cout << text << std::endl;
}

void UI::wrongInput() {
    print(IllegalNumber);
}

int UI::getIndexIn() const {
    return indexIn;
}

void UI::mainLoop() {
    AccountUI();
    if (!this->is_loggedIn) {
        exit();
    }

    while (UI::runtime) {
        print(UI::menuText);
        std::cin >> indexIn;

        if (indexIn == 6) {
            exit();
        }

    };


}

UI::UI(): indexIn(0), is_loggedIn(false) {
    print(UI::welcomeText);
}

void UI::AccountUI() {
    while (!is_loggedIn) {
        print(UI::loginMenu);
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
    this->is_loggedIn = true;
}

void UI::makeAcc() { // TODO finish if needed
    this->is_loggedIn = false;
}

void UI::exit() {
    UI::runtime = false;
    this->is_loggedIn = false;
    print(UI::goodbye);
}


