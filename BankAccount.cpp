#include <random>
#include <utility>
#include "BankAccount.hpp"

BankAccount::BankAccount(const BankAccount &other): ID(other.ID), userMoney(other.userMoney) {
    this->name = other.name;
    this->isMale = other.isMale;
    this->userShares = other.userShares;
    this->isWorker = other.isWorker;
}

BankAccount::BankAccount(): ID(BankAccount::generateID()), userMoney(), isMale(false), isWorker(false) {}

BankAccount::BankAccount(const Money& in, std::string nameIn, bool isMaleIn,bool isWorkerIn):
ID(BankAccount::generateID()), name(std::move(nameIn)), isWorker(isWorkerIn), isMale(isMaleIn)
{
    if (in.getValue() < 0) {
        throw Exceptions(NegativeMoney, "Negative money was given.");
    }
    this->userMoney = in;
}


Money BankAccount::getMoney() const {
    return userMoney;
}

const std::string &BankAccount::getName() const {
    return name;
}

unsigned int BankAccount::getId() const {
    return ID;
}

void BankAccount::setMoney(const Money& in) {
    this->userMoney = in;
}

int BankAccount::generateID() {

    // Safe C++ 11 random generator

    std::random_device randomizer;
    std::mt19937 gen(randomizer());
    std::uniform_int_distribution<>dis(1000,9999);

    return dis(gen);
}

void BankAccount::setName(const std::string &newUserName) {
    this->name = newUserName;
}

void BankAccount::addMoney(const Money &in) {
    this->userMoney += in;
}

void BankAccount::substractMoney(const Money &in) {
    this->userMoney -= in;
}

std::string BankAccount::getGender() const {
    if (isMale) {
        return {"Male"};
    }
    return {"Female"};
}

bool BankAccount::getisWorker() const {
    return isWorker;
}

void BankAccount::setIsWorker(bool isWorkerIn) {
    BankAccount::isWorker = isWorkerIn;
}

void BankAccount::BuyShares(Share& type, int amount) { // TODO tesztelni

    if (!userShares.empty()) {
        for (auto i = userShares.begin(); i < userShares.end(); i++) {
            if ((*i).getMaster() == &type) {
                type.buyShares(amount, (*i));
                return;
            }
        }
    }
    OwnedShare temp;
    type.buyShares(amount, temp);
    if (temp.getMaster() != nullptr) {
        this->userShares.push_back(temp);

    }
}

void BankAccount::SellShares(Share& type, int amount) { //TODO tesztelni
    if (!userShares.empty()) {
        for (auto i = userShares.begin(); i < userShares.end(); i++) {
            if ((*i).getMaster() == &type) {
                type.sellShares(amount, (*i));

                if ((*i).getAmount() == 0) {
                    userShares.erase(i);
                }

                return;
            }
        }
    }
    throw Exceptions(NotEnoughShares, "Tried to sell shares, but didn't buy earlier. (empty user)");
}

OwnedShare BankAccount::getIndex(int n) { // TODO TOROLNI MAJD
    return this->userShares.at(n);
}


std::ostream& operator<<(std::ostream& stream, const BankAccount& in) {
    stream << "Name: " << in.getName() << " (id: " << in.getId() << ") " << in.getGender() <<" : " << in.getMoney();
    return stream;
}
