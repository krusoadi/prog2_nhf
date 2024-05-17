#include "../headers/FileManager.hpp"
#include <utility>

FileManager::FileManager(std::string userFile, std::string accountFile, std::string shareFile):
        UserFileName(std::move(userFile)), AccountsFileName(std::move(accountFile)), BankShareFileName(std::move(shareFile)){}

void FileManager::loadUserFile(TContainer<User>& users) {

    std::ifstream userFile(this->UserFileName, std::ios::in);

    if (!userFile.is_open()) {
        throw Exceptions(FileError, "(FileManager) Couldn't open user info file, are you sure it exists?");
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
        throw Exceptions(FileError, "(FileManager) Couldn't open BankAccount info file, are you sure it exists?");
    }

    for (std::string line; std::getline(AccFile, line);)
    {
        std::istringstream lineStream(line);

        std::string fID; std::getline(lineStream, fID, ';');
        std::string Name; std::getline(lineStream, Name, ';');
        std::string fMale; std::getline(lineStream, fMale, ';');
        std::string fMoneyAmount; std::getline(lineStream, fMoneyAmount, ';');
        std::string fCurrency; std::getline(lineStream, fCurrency, ';');
        std::string fisWorker; std::getline(lineStream, fisWorker, '|');

        IDManager tempId(std::stoi(fID));
        bool tempMale = std::stoi(fMale);
        Money tempMoney(std::stod(fMoneyAmount), (CurrencyTypes)std::stoi(fCurrency));
        bool tempWorker = std::stoi(fisWorker);

        BankAccount tempAcc(tempMoney, Name, tempMale, tempWorker);

        for (std::string ShareLine; std::getline(AccFile, ShareLine, '|');) {
            std::istringstream ShareLineStream(ShareLine);
            OwnedShare tempOS = loadOwnedShare(ShareLineStream);
            tempAcc.loadShares(tempOS);

        }
        for (auto &it :users) {
            if (tempAcc == it.getUserBank()) {
                it.setUserBank(tempAcc);
            }
        }
    }
}

OwnedShare FileManager::loadOwnedShare(std::istringstream &lineStream) {
    std::string fOSMID; std::getline(lineStream, fOSMID, ';'); // file OwnedShare Master ID
    std::string fAmount; std::getline(lineStream, fAmount); // OwnedShare Amount

    IDManager OSMIDTemp(std::stoi(fOSMID));
    int AmountTemp =std::stoi(fAmount);

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

void FileManager::saveUsers(const TContainer<User>& users) {
    saveUserFile(users);
    saveAccountsFile(users);
}

void FileManager::saveUserFile(const TContainer<User>& users) const {
    std::ofstream UserFile(this->UserFileName, std::ios::out);

    if (!UserFile.is_open()) {
        throw Exceptions(FileError, "(FileManager) Couldn't open user file for writing, try again.");
    }

    for (auto &i : users) {

    }
}

void FileManager::saveAccountsFile(const TContainer<User>& users) {

}
