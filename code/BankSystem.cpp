#include "../headers/BankSystem.hpp"

BankSystem::BankSystem(): bankMoney(Money()), users(TContainer<User>()),
                          bankShares(TContainer<Share>())  {}

BankSystem::BankSystem(const Money &initMoney): users(TContainer<User>()),
                          bankShares(TContainer<Share>()), bankMoney(initMoney) {}

const Money &BankSystem::getBankMoney() const {
    return bankMoney;
}

Share &BankSystem::getShareByChild(const OwnedShare& in) const {
    return this->bankShares[this->bankShares.search(in)];
}

void BankSystem::addNewUser(const User& user) {
    try {this->users.add_back(user);}
    catch (Exceptions &e) {std::cerr << e.what() << " Didn't add new user.\n";}
}

void BankSystem::addBankShares(const Share &ShareIn) {
    try {this->bankShares.add_back(ShareIn);}
    catch (Exceptions &e) {std::cerr << e.what() << " Didn't add new Share.\n";}
}

void BankSystem::deleteUser(const User &user) {
    try {this->users.pop_index(this->users.search(user));}
    catch (Exceptions &e) {std::cerr << e.what() << " Didn't delete User.\n";}
}

void BankSystem::deleteBankShares(const Share &ShareIn) {
    try {this->bankShares.pop_index(this->bankShares.search(ShareIn));}
    catch (Exceptions &e) {std::cerr << e.what() << " Didn't delete Share.\n";}
}

void BankSystem::loadUsers(const std::string& filename) {
    std::ifstream userFile(filename, std::ios::in);

    if (!userFile.is_open()) {
        throw Exceptions(FileError, "Couldn't open user info file, are you sure it exists?");
    }

    for (std::string line; std::getline(userFile, line);) {
        std::string fUsername;
        std::string fPassword;
        std::string fAccId;

        std::istringstream lineStream(line);

        std::getline(lineStream, fUsername, ';');
        std::getline(lineStream, fPassword, ';');
        std::getline(lineStream, fAccId, ';');

        User readIn(fUsername, fPassword, BankAccount(IDManager(std::stoi(fAccId))));

        users.add_back(readIn);
    }
}

void BankSystem::loadBankAccounts(const std::string &filename) {
    std::ifstream AccFile(filename, std::ios::in); //AccountsFile

    if (!AccFile.is_open()) {
        throw Exceptions(FileError, "Couldn't open user info file, are you sure it exists?");
    }

    for (std::string line; std::getline(AccFile, line);)
    {
        std::istringstream lineStream(line);

        std::string fID; std::getline(lineStream, fID, ';');
        std::string Name; std::getline(lineStream, Name, ';');
        std::string fMale; std::getline(lineStream, fMale, ';');
        std::string fMoneyAmount; std::getline(lineStream, fMoneyAmount, ';');
        std::string fCurrency; std::getline(lineStream, fCurrency, ';');
        std::string fisWorker; std::getline(lineStream, fisWorker, ';');

        IDManager tempId(std::stoi(fID));
        bool tempMale = std::stoi(fMale);
        Money tempMoney(std::stod(fMoneyAmount), (CurrencyTypes)std::stoi(fCurrency));
        bool tempWorker = std::stoi(fisWorker);

        BankAccount tempAcc(tempMoney, Name, tempMale, tempWorker);

        for (auto &it :users) {
            if (tempAcc == it.getUserBank()) {
                it.setUserBank(tempAcc);
            }
        }
    }
}

void BankSystem::loadOwnedShares(const std::string &filename) {
    std::ifstream OSFile(filename, std::ios::in); //OwnedShareFile

    if (!OSFile.is_open()) {
        throw Exceptions(FileError, "Couldn't open user info file, are you sure it exists?");
    }

    for (std::string line; std::getline(OSFile, line);) {
        std::istringstream lineStream(line);

        std::string fUserID; std::getline(lineStream, fUserID, ';'); //ID of the User who owns it
        std::string fOSMID; std::getline(lineStream, fOSMID, ';'); // file OwnedShare Master ID
        std::string fAmount; std::getline(lineStream, fAmount, ';'); // OwnedShare Amount

        int userIDTemp = std::stoi(fUserID);
        IDManager OSMIDTemp(std::stoi(fOSMID));
        int AmountTemp =std::stoi(fAmount);

        OwnedShare tempOS(AmountTemp);
        tempOS.setMasterShareId(OSMIDTemp.getId());

        for (auto &i: users) {
            if (i.getUserBank().getId() == userIDTemp) {
                i.loadBankaccount().loadShares(tempOS);
            }
        }
    }
}

