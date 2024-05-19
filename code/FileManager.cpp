#include "../headers/FileManager.hpp"
#include <utility>

FileManager::FileManager(std::string userFile, std::string accountFile, std::string shareFile) :
        UserFileName(std::move(userFile)), AccountsFileName(std::move(accountFile)),
        BankShareFileName(std::move(shareFile)) {}

void FileManager::loadUserFile(TContainer<User> &users) {

    std::ifstream userFile(this->UserFileName, std::ios::in);

    if (!userFile.is_open()) {
        throw Exceptions(FileError, "(FileManager) Couldn't open user info file, are you sure it exists?\n");
    }

    for (std::string line; std::getline(userFile, line);) {
        std::string fUsername;
        std::string fPassword;
        std::string fAccId;

        std::istringstream lineStream(line);

        std::getline(lineStream, fUsername, ';');
        std::getline(lineStream, fPassword, ';');
        std::getline(lineStream, fAccId);

        User readIn(fUsername, fPassword, BankAccount(IDManager(std::stoi(fAccId))));

        users.add_back(readIn);
    }
}

void FileManager::loadAccountFile(TContainer<User> &users) {
    std::ifstream AccFile(this->AccountsFileName, std::ios::in); //AccountsFile

    if (!AccFile.is_open()) {
        throw Exceptions(FileError, "(FileManager) Couldn't open BankAccount info file, are you sure it exists?\n");
    }

    for (std::string line; std::getline(AccFile, line);) {
        std::istringstream lineStream(line);

        std::string fID;
        std::getline(lineStream, fID, ';');
        std::string Name;
        std::getline(lineStream, Name, ';');
        std::string fMale;
        std::getline(lineStream, fMale, ';');
        std::string fMoneyAmount;
        std::getline(lineStream, fMoneyAmount, ';');
        std::string fCurrency;
        std::getline(lineStream, fCurrency, ';');
        std::string fisWorker;
        std::getline(lineStream, fisWorker, '|');

        int tempId = std::stoi(fID);
        bool tempMale = std::stoi(fMale);
        Money tempMoney(std::stod(fMoneyAmount), (CurrencyTypes) std::stoi(fCurrency));
        bool tempWorker = std::stoi(fisWorker);

        BankAccount tempAcc(tempMoney, Name, tempMale, tempWorker);

        for (std::string ShareLine; std::getline(lineStream, ShareLine, '|');) {
            std::istringstream ShareLineStream(ShareLine);
            OwnedShare tempOS = loadOwnedShare(ShareLineStream);
            tempAcc.loadOShares(tempOS);

        }
        for (auto &it: users) {
            if (tempId == it.getUserBank().getId()) {
                it.setUserBank(tempAcc);
                return;
            }
        }
    }
}

OwnedShare FileManager::loadOwnedShare(std::istringstream &lineStream) {
    std::string fOSMID;
    std::getline(lineStream, fOSMID, ';'); // file OwnedShare Master ID
    std::string fAmount;
    std::getline(lineStream, fAmount); // OwnedShare Amount

    IDManager OSMIDTemp(std::stoi(fOSMID));
    int AmountTemp = std::stoi(fAmount);

    OwnedShare tempOS(AmountTemp);
    tempOS.setMasterShareId(OSMIDTemp.getId());
    return tempOS;
}

TContainer<User> FileManager::loadUsers() {
    TContainer<User> temp;

    loadUserFile(temp);
    loadAccountFile(temp);
    return temp;
}

void FileManager::saveUsers(const TContainer<User> &users) {
    saveUserFile(users);
    saveAccountsFile(users);
}

void FileManager::saveUserFile(const TContainer<User> &users) const {
    std::ofstream UserFile(this->UserFileName, std::ios::out);

    if (!UserFile.is_open()) {
        throw Exceptions(FileError, "(FileManager) Couldn't open user file for writing, try again.\n");
    }
    if (!users.isEmpty()) {
        for (const auto &user: users) {
            UserFile << user.getUsername() << ";" << user.getHashedPw() << ";" << user.getUserBank().getId() << "\n";
        }
    }
}

void FileManager::saveAccountsFile(const TContainer<User> &users) {
    std::ofstream AccountsFile(this->AccountsFileName, std::ios::out);

    if (!AccountsFile.is_open()) {
        throw Exceptions(FileError, "(FileManager) Couldn't open user file for writing, try again.\n");
    }
    if (!users.isEmpty()) {
        for (const auto &user: users) {
            BankAccount userAcc = user.getUserBank();
            Money userMoney = userAcc.getMoney();
            AccountsFile << userAcc.getId() << ";" << userAcc.getName() << ";" << (int) userAcc.getIsMale() << ";";
            AccountsFile << userMoney.getValue() << ";" << (int) userMoney.getCurrency() << ";"
                         << (int) userAcc.getIsWorker() << "|";
            if (!userAcc.getUserShares().isEmpty()) {
                for (const auto &OShare: userAcc.getUserShares()) {
                    AccountsFile << OShare.getMasterShareId() << ";" << OShare.getAmount() << "|";
                }
            }
            AccountsFile << "\n";
        }
    }
}

void FileManager::loadShareFile(TContainer<Share> &shares) {
    std::ifstream ShareFile(this->BankShareFileName, std::ios::in);

    if (!ShareFile.is_open()) {
        throw Exceptions(FileError, "(FileManager) Could not open ShareFile, are you sure it exists?");
    }
    for (std::string line; std::getline(ShareFile, line);) {
        std::istringstream lineStream(line);

        std::string fID;
        std::getline(lineStream, fID, ';');
        std::string fName;
        std::getline(lineStream, fName, ';');
        std::string fValue;
        std::getline(lineStream, fValue, ';');
        std::string fCurrency;
        std::getline(lineStream, fCurrency, ';');
        std::string fAvailable;
        std::getline(lineStream, fAvailable);

        int tempID = std::stoi(fID);
        double tempVal = std::stod(fValue);
        auto tempCurr = (CurrencyTypes) std::stoi(fCurrency);
        int tempAvailable = std::stoi(fAvailable);
        Share finalShare(tempID, fName, Money(tempVal,tempCurr), tempAvailable);
        shares.add_back(finalShare);
    }

    if(shares.isEmpty()) {
        throw std::runtime_error("Shares couldn't be loaded, will generate new shares."
                                          "All users loose their previous shares, and get compensation.");
    }
}

void FileManager::saveShareFile(const TContainer<Share>& out) {
    if (out.isEmpty()) {
        throw std::runtime_error("There is no share to save, the program will generate new "
                                          "shares, all the users who lose their share will be compensated.")
    }

    std::ofstream ShareFile(BankShareFileName, std::ios::out);

    if (!ShareFile.is_open()) {
        throw Exceptions(FileError, "(FileManager) Couldn't open ShareFile to write.");
    }

    for (const auto& it : out) {
        ShareFile << it.getShareId() << ';' << it.getName() << ';' << it.getValue().getValue() << ';';
        ShareFile << (int)it.getValue().getCurrency() << ';' << it.getAvailable() << '\n';
    }
}

void FileManager::resetShareFile() {
    Share temp1("Apple", Money(500, HUF), 100);
    Share temp2("Tesla", Money(750, HUF), 200);
    Share temp3("Meta", Money(3, EUR), 125);
    Share temp4("BME", Money(5, USD), 150);
    Share temp5("Mol", Money(200, HUF), 600);

    TContainer<Share> list;
    list.add_back(temp1);
    list.add_back(temp2);
    list.add_back(temp3);
    list.add_back(temp4);
    list.add_back(temp5);

    saveShareFile(list);

}

TContainer<Share> FileManager::loadShares() {
    TContainer<Share> retVal;

    try {
        loadShareFile(retVal);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what();
        resetShareFile();
        loadShareFile(retVal);
    }
    return retVal;
}

void FileManager::saveShares(const TContainer<Share>& in) {
    try {
        saveShareFile(in);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what();
        resetShareFile();
    }
}
