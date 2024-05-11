#include "../headers/IDManager.h"

TContainer<int> IDManager::reservedIDs = TContainer<int>();

int IDManager::getRandomNumber() {
    std::random_device randomizer;
    std::mt19937 gen(randomizer());
    std::uniform_int_distribution<>dis(10000,99999);
    return dis(gen);
}

int IDManager::generateID() {
    int UniqueID = getRandomNumber();

    if (!reservedIDs.isEmpty()) {
        while (reservedIDs.search(UniqueID) == -1) {
            UniqueID = getRandomNumber();
        }
    }
    reservedIDs.add_back(UniqueID);
    return UniqueID;
}

unsigned int IDManager::getId() const {
    return id;
}

IDManager::IDManager(): id(generateID()) {}

IDManager::IDManager(const IDManager &other): id(other.id) {}

IDManager::IDManager(int previousID) {
    if (!reservedIDs.isEmpty()) {
        try {
            if (reservedIDs.search(previousID) != -1) {
                throw Exceptions(IDAlreadyExists, "Given ID is already used in the system,"
                                                  " generated a new.");
            }
        } catch (Exceptions &e) {
            int newID = generateID();
            std::cerr << e.what() << "new id : " << newID;
            this->id = newID;
            return;
        }
    }
    this->id = previousID;
}

std::ostream & operator<<(std::ostream& stream, const IDManager& in) {
    return stream << "ID:" << in.getId();
}
