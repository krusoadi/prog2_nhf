
#ifndef PROG2_NHF_IDMANAGER_H
#define PROG2_NHF_IDMANAGER_H
#include "TContainer.hpp"
#include <random>
#include "Exceptions.hpp"

class IDManager {
private: // Static private variables
    static TContainer<int> reservedIDs; // Already in use IDs
    int static getRandomNumber(); // Random number generator for IDs
    int static generateID(); // This does the checking of the generated, id, and adding it to the reserved

private: // Object related private variables
    int id; // Actual ID

public:
    IDManager(); // Only use this, when new ID will be assigned
    IDManager(int previousID); // Only use this, when the object is read from file, and already has an ID

    IDManager(const IDManager&other);
    ~IDManager() = default;

    // Getter
    [[nodiscard]] unsigned int getId() const;
};

std::ostream & operator<<(const IDManager& in, std::ostream& stream);


#endif //PROG2_NHF_IDMANAGER_H
