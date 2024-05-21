#include "../headers/UI.hpp"

bool UI::runtime = true;

const std::string UI::welcomeText = "\nWelcome To NewVille Bank, this program is made by Adam Krusoczki"
                                    "\nMy github link is www.github.com/krusoadi\n\n";

const std::string UI::menuText = "\nPlease type in your selected menu point. Options:\n\n"
                                 "1. Deposit Money\n"
                                 "2. Withdraw Money\n"
                                 "3. Check my account\n"
                                 "4. Shares\n"
                                 "5. View Currency\n"
                                 "6. Convert to new Currency\n"
                                 "7. Clear Screen (cls)\n"
                                 "8. Log out\n";

const std::string UI::shareMenuText = "\nPlease type in your selected menu point. Options:\n\n"
                                      "1. Show information about the shares\n"
                                      "2. Buy shares\n"
                                      "3. Sell shares\n"
                                      "4. Show my shares\n"
                                      "5. Return\n";

const std::string UI::accountTextMenu = "Please type in your selected menu point. Options:\n\n"
                                        "1. Login\n"
                                        "2. Register\n"
                                        "3. Exit\n";

const std::string UI::usernameTXT = "\nUsername >";

const std::string UI::passwordTXT = "\nPassword >";

const std::string UI::goodbye = "\nThank you for using this app, have a nice day! Goodbye!\n";

const std::string UI::IllegalNumber = "\nThe menu point you gave is not defined. Please retry\n";

void UI::print(const std::string &text) {
    std::cout << text;
}

UI::~UI() {
    this->manager.saveUsers(this->system.getUsers());
    this->manager.saveShareFile(this->system.getBankShares());
}

void UI::wrongMenuPoint() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    print(IllegalNumber);
}

void UI::wrongInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    print("\nThe input was wrong, please try again\n");
}

void UI::mainLoop() {
    AccountUI();
    if (!this->is_loggedIn) {
        UI::runtime = false;
    }

    while (UI::runtime) {
        print(UI::menuText);
        print("\n>");
        std::cin >> indexIn;
        mainMenuFunctions();
    };

}

UI::UI(const BankSystem &systemIn, const FileManager &managerIn) : indexIn(0), is_loggedIn(false),
                                                                   manager(managerIn), system(systemIn) {
    print(UI::welcomeText);
    Currency::updateCurrency();
    std::cout << std::fixed << std::setprecision(3) <<std::endl;
}

void UI::AccountUI() {
    while (!is_loggedIn) {
        print(UI::accountTextMenu);
        print("\n>");
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
                wrongMenuPoint();
                break;
        }
    }
}

void UI::logIn() {
    std::string userName;
    std::string Password;

    print(usernameTXT);

    std::cin >> userName;
    if (!system.isUserNameReserved(userName)) {
        print("\nThere is no account with this username, please try again!\n");
        return;
    }

    print(passwordTXT);
    Password = safeInput();
    std::string hashed = hashStr(Password);

    try {
        const User &found = system.getConstUser(userName);
        if (!found.MatchPassword(hashed)) {
            print("Incorrect password, try again!\n");
            return;
        }
        print("\n\nSuccessfully logged in! Welcome back\n");
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

    print(usernameTXT);

    std::cin >> newUserName;

    if (system.isUserNameReserved(newUserName)) {
        print("\nUsername is already in use please choose an other one.\n");
        return;
    }

    print(passwordTXT);
    newPassword = safeInput();

    print("\nType in your first name >");

    std::cin >> name;

    if (hasDigit(name)) {
        print("\nDigits cannot be in names\n");
        return;
    }

    print("\nType in your last name >");
    std::string last;
    std::cin >> last;


    if (hasDigit(last)) {
        print("\nDigits cannot be in names\n");
        return;
    }

    name += " " + last;

    print("\n Are you a male (y/n): ");

    bool isMale;
    std::string male;
    std::cin >> male;

    if (male == "y") {
        isMale = true;
    } else if (male == "n") {
        isMale = false;
    } else {
        wrongInput();
        return;
    }

    newUser.setUsername(newUserName);
    newUser.setHashedPw(hashStr(newPassword));
    newUser.setUserBank(BankAccount(Money(0, EUR), name, isMale, true));
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

std::string UI::hashStr(const std::string &in) { // The only point of this function is to not store the passwords as they are.
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
    if (checkAnswerFail()) {
        return;
    }

    if (amount < 0.0) {
        print("\nCannot deposit negative amount of money!\n");
        return;
    }

    print("\n");

    print("Please select currency (1 = EUR, 2 = HUF, 3 = USD >");
    int type;
    CurrencyTypes finalType;
    std::cin >> type;

    if (checkAnswerFail()) {
        return;
    }

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
            wrongMenuPoint();
            return;
    }
    Money in(amount, finalType);
    this->system.getUserByUsername(thisUser.getUsername()).getUserBank().addMoney(in);
    refreshUser();
    print("\nSuccessfully added the amount of money.\n");
}

void UI::refreshUser() {
    auto refresh = this->system.getConstUser(thisUser.getUsername());
    this->thisUser = refresh;
}

void UI::withdrawMoney() {
    print("Type in the amount you want to withdraw >");
    double amount;

    try {
        std::cin >> amount;
    } catch (...) {
        wrongMenuPoint();
        return;
    }

    if (amount <= 0.0) {
        print("\nCannot withdraw negative amount of money!\n");
        return;
    }

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
            wrongMenuPoint();
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
        case 4:
            ShareMenu();
            break;
        case 5:
            Currency::printCurrency();
            break;
        case 6:
            convertMyCurrency();
            return;
        case 7 :
            clearScreen();
            break;
        case 8:
            exit();
            return;
        default:
            wrongMenuPoint();
            return;
    }
}

void UI::boot() {
    try {
        this->system.loadUsers(this->manager.loadUsers());
    }
    catch (const Exceptions &e) {
        std::cerr << e.what() << std::endl;
        if (e.getType() == FileError) {
            std::cerr << "\nData could not be loaded. The program continues, with new save.\n" << std::endl;
        }
    }

    try {
        this->system.loadBankShares(this->manager.loadShareFile());
    }
    catch (const Exceptions &e) {
        std::cerr << e.what() << std::endl;
        this->manager.resetShareFile();
        this->system.loadBankShares(this->manager.loadShareFile());
    }
    this->mainLoop();
}

void UI::ShareMenu() {
    print(shareMenuText + "\n");
    ShareMenuFunctions();
}

void UI::ShareMenuFunctions() {
    print("\n>");
    std::cin >> this->indexIn;

    switch (indexIn) {
        case 1:
            printBankShares(); // Checked
            return;
        case 2:
            buyShares(); // Checked
            break;
        case 3:
            sellShares(); // Checked
            break;
        case 4:
            showMyShares();
            break;
        case 5:
            return;
        default:
            wrongMenuPoint();
            break;
    }
}

void UI::printBankShares() {
    if (this->system.getBankShares().isEmpty()) {
        return;
    }
    int index = 0;

    for (const auto &i: this->system.getBankShares()) {
        std::cout << ++index << ". "<< i << std::endl;
    }
}

void UI::buyShares() {
    printBankShares();

    int index;
    print("Type in the index of the desired share >");

    std::cin >> index;
    if (checkAnswerFail()) {
        return;
    }

    if(index > this->system.getBankShares().size() || index < 1) {
        print("\nThe index you gave is not existent!\n");
        return;
    }

    print("\n");

    int amount;
    print("Type in the desired amount >");

    std::cin >> amount;
    if (checkAnswerFail()) {
        return;
    }

    if (amount < 1) {
        print("\nZero or negative amount of shares cannot be bought!\n");
        return;
    }

    print("\n");

    User& temp = this->system.getUserByUsername(this->thisUser.getUsername());

    try {
        temp.getUserBank().BuyShares(this->system.getBankShares()[index - 1], amount);
    } catch (const Exceptions &e) { // Here it does not matter if we get WrongMaster, or NotEnoughShares
        std::cerr << e.what(); // exception, because we cannot continue either way.
        return;
    }
    refreshUser();
}

void UI::sellShares() {
    User &current = this->system.getUserByUsername(this->thisUser.getUsername());
    auto currentShares = current.getUserBank().getUserShares();
    int index = 0;

    if (currentShares.isEmpty()) {
        print("\nYou do not have any shares to sell.\n");
        return;
    }

    for (const auto &it:currentShares) {
        std::cout << ++index << ". " << it << ":" << std::endl;
    }

    print("\n");

    print("Type in the index of the desired share >");


    std::cin >> index;
    if (checkAnswerFail()) {
        return;
    }


    if(index > currentShares.size() || index < 1) {
        print("\nThe index you gave is not existent\n");
        return;
    }

    print("\n");

    int amount;
    print("Type in the desired amount >");


    std::cin >> amount;
    if (checkAnswerFail()) {
        return;
    }


    if (amount < 1) {
        print("\nZero or negative amount of shares cannot be bought!\n");
        return;
    }

    OwnedShare &selected = currentShares[index-1];
    Share& masterShare = this->system.getShareByChild(selected);

    try {
        current.getUserBank().SellShares(masterShare, amount);
    } catch (const Exceptions &e) { // Same as in buying, we cannot continue with either exceptions thrown
        std::cerr << e.what(); // so we let the user know the error and return. (WrongMaster probably can't happen.)
        return;
    }
    refreshUser();
    print("\nSuccessfully sold the shares!\n");
}

void UI::convertMyCurrency() {
    Currency::printCurrency();
    print("\nPlease select currency (1 = EUR, 2 = HUF, 3 = USD, 4 = return) >");
    int type;
    CurrencyTypes finalType;

    try {
    std::cin >> type;
    } catch (...) {
        wrongMenuPoint();
        return;
    }
    

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
        case 4:
            return;
        default:
            wrongMenuPoint();
            return;
    }


    User& current = this->system.getUserByUsername(this->thisUser.getUsername());
    auto& newMoney = current.getUserBank().getMoney().convertCurrency(finalType);
    current.getUserBank().setAccountMoney(newMoney);
    refreshUser();
    print("\nYour money has been converted successfully!\n");
    std::cout << "Converted money: " <<  newMoney << std::endl;
}

bool UI::hasDigit(const std::string &in) {
    if (!in.empty()) {
        for (const char c : in) {
            if (isdigit(c)) {
                return true;
            }
        }
    }
    return false;
}

void UI::clearScreen() {
    print("\033[2J\033[1;1H");
}

void UI::showMyShares() {
    auto userShares = this->thisUser.getUserBank().getUserShares();
    print("\n");

    if (userShares.isEmpty()) {
        print("\nYou don't have any shares bought.\n");
        return;
    }
    for (const auto &OS: userShares) {
        auto Master = this->system.getShareByChild(OS);
        std::cout << Master.getName() << ": " << OS << " value: " << OS.showValue(&Master) << std::endl;
    }
}

bool UI::checkAnswerFail() {
    if (std::cin.fail()) {
        wrongInput();
        return true;
    }
    return false;
}







