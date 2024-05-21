#ifndef PROG2_NHF_FILEMANAGER_HPP
#define PROG2_NHF_FILEMANAGER_HPP

#include "Exceptions.hpp"
#include "TContainer.hpp"
#include "User.hpp"
#include <fstream>
#include <sstream>

class FileManager {
private: // File Name Variables
    std::string UserFileName; // Name of the file where users login data is stored
    std::string AccountsFileName; // Name of the file where users bank account is stored
    std::string BankShareFileName; // Name of the file where Banks Shares are stored

private: // Private File Data Loaders (used by loadUsers())
    void loadUserFile(TContainer<User> &users); // Loads users data from the UserFileName
    void loadAccountFile(TContainer<User> &users); // Loads users accounts from the AccountsFileName
    static OwnedShare loadOwnedShare(std::istringstream &lineStream); // Loads users shares from a given string

private: // Private File Data Savers
    void saveUserFile(const TContainer<User> &users) const; // Saves users data to UserFile
    void saveAccountsFile(const TContainer<User> &users); // Saves users accounts (and shares) to UserFile

public:
    // Constructors and Destructors

    FileManager(std::string userFile, std::string accountFile, std::string shareFile);
    FileManager(const FileManager &other) = default;
    ~FileManager() = default;

    // User Save/Load methods

    TContainer<User> loadUsers(); // Public function to load users for UI
    void saveUsers(const TContainer<User> &users); // Public Function to save users for UI

    // Share Save/Load methods

    void saveShareFile(const TContainer<Share>& out); // Saves Shares to BankShareFileName
    TContainer<Share> loadShareFile(); // Loads Shares from the BankShareFileName
    void resetShareFile(); // Resets Share File if error is encountered
};

#endif //PROG2_NHF_FILEMANAGER_HPP
