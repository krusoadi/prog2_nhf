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
        while (reservedIDs.search(UniqueID) != -1) {
            UniqueID = getRandomNumber();
        }
    }
    reservedIDs.add_back(UniqueID);
    return UniqueID;
}

IDManager::IDManager(): id(generateID()) {}

IDManager::IDManager(int previousID) {
    try {
        if (id < 10000 || id > 99999) {
            throw Exceptions(InvalidId, "The ID is invalid, not between the supported bounds,"
                                        " generated a new");
        }

        if (!reservedIDs.isEmpty()) {
            if (reservedIDs.search(previousID) != -1) {
                throw Exceptions(IDAlreadyExists, "Given ID is already used in the system,"
                                                  "generated a new. ");
            }
        }
    } catch (Exceptions & e) {
        int newID = generateID();
        std::cerr << e.what() << "New ID : " << newID << std::endl;
        this->id = newID;
        reservedIDs.add_back(newID);
        return;
    }

    this->id = previousID;
    reservedIDs.add_back(previousID);
}

unsigned int IDManager::getId() const {
    return id;
}

bool IDManager::operator==(const IDManager &other) const {
    return this->id == other.id;
}

std::ostream & operator<<(std::ostream& stream, const IDManager& in) {
    return stream << "ID: " << in.getId();
}
