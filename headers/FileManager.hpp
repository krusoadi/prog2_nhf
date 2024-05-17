#ifndef PROG2_NHF_FILEMANAGER_HPP
#define PROG2_NHF_FILEMANAGER_HPP
#include "Exceptions.hpp"
#include "TContainer.hpp"
#include "User.hpp"
#include <fstream>
#include <sstream>

class FileManager {
private: // File Name Variables
    std::string UserFileName;
    std::string AccountsFileName;
    std::string BankShareFileName;
private: // Private File Data Loaders
    void loadUserFile(TContainer<User>& users);
    void loadAccountFile(TContainer<User>& users);
    static OwnedShare loadOwnedShare(std::istringstream &lineStream);
private:
    void saveUserFile(const TContainer<User>& users) const;
    void saveAccountsFile(const TContainer<User>& users);
public:
    FileManager(std::string  userFile, std::string  accountFile, std::string  shareFile);
    FileManager(const FileManager& other) = default;
    TContainer<User> loadUsers();
    void saveUsers(const TContainer<User>& users);

};


#endif //PROG2_NHF_FILEMANAGER_HPP
