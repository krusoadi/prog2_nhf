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
    std::cout << text;
}

UI::~UI() {
    this->manager.saveUsers(this->system.getUsers());
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
        mainMenuFunctions();
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

void UI::logIn() {
    std::string userName;
    std::string Password;

    print("\nType in your selected username:");

    std::cin >> userName;
    if (!system.isUserNameReserved(userName)) {
        print("There is no account with this username, please try again!\n");
        return;
    }

    print("\n Type in your password");
    Password = safeInput();
    std::string hashed = hashStr(Password);

    try {
        const User &found = system.searchByUserName(userName);
        if (!found.MatchPassword(hashed)) {
            print("Incorrect password, try again!\n");
            return;
        }
        print("\nSuccessfully logged in! Welcome back\n");
        this->is_loggedIn = true;
        this->thisUser = found;
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
        print("\nUsername is already in use please choose an other one.\n");
        return;
    }

    print("\n Type in your password >");
    newPassword = safeInput();
    print("\nType in your first name >");
    std::cin >> name;
    print("\nType in your last name >");
    std::string last;
    std::cin >> last;
    name += " " + last;

    newUser.setUsername(newUserName);
    newUser.setHashedPw(hashStr(newPassword));
    newUser.setUserBank(BankAccount(Money(0, EUR), name, false, true));
    system.addNewUser(newUser);
    manager.saveUsers(system.getUsers());
    this->thisUser = newUser;

    print("\nCongratulations, you've just made your first account.\n");
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

void UI::depositMoney() {
    print("Type in the amount you want to deposit >");
    double amount;
    std::cin >> amount;

    print("\n");

    print("Please select currency (1 = EUR, 2 = HUF, 3 = USD >");
    int type;
    CurrencyTypes finalType;
    std::cin >> type;

    switch (type) {
        case 1:
            finalType = EUR;
            break;
        case 2:
            finalType = HUF;
            break;
        case 3:
            finalType = USD;
            break;
        default:
            wrongInput();
            return;
    }
    Money in(amount, finalType);
    this->system.getUserByUsername(thisUser.getUsername()).getUserBank().addMoney(in);
    refreshUser();
    print("\nSuccessfully added the amount of money.\n");
}

void UI::refreshUser() {
    auto refresh = this->system.searchByUserName(thisUser.getUsername());
    this->thisUser = refresh;
}

void UI::withdrawMoney() {
    print("Type in the amount you want to withdraw >");
    double amount;
    std::cin >> amount;

    print("\n");

    print("Please select currency (1 = EUR, 2 = HUF, 3 = USD >");
    int type;
    CurrencyTypes finalType;
    std::cin >> type;

    switch (type) {
        case 1:
            finalType = EUR;
            break;
        case 2:
            finalType = HUF;
            break;
        case 3:
            finalType = USD;
            break;
        default:
            wrongInput();
            return;
    }
    Money in(amount, finalType);
    try {
        this->system.getUserByUsername(thisUser.getUsername()).getUserBank().subtractMoney(in);
    } catch (const Exceptions &e) {
        if (e.getType() == NegativeMoney) {
            print(e.what());
            return;
        } else {
            std::cerr << e.what();
            return;
        }
    }
    refreshUser();
    print("\nSuccessfully withdrew the amount of money.\n");
}

void UI::myAccount() {
    print("Your account: ");
    std::cout << this->thisUser.getUserBank() << std::endl;
}

void UI::mainMenuFunctions() {
    switch (indexIn) {
        case 1:
            depositMoney();
            break;
        case 2:
            withdrawMoney();
            break;
        case 3:
            myAccount();
            break;
        case 6:
            exit();
            return;
        default:
            wrongInput();
            return;
    }
}


