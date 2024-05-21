#include <random>
#include <utility>
#include "../headers/BankAccount.hpp"

BankAccount::BankAccount(const BankAccount &other) : ID(other.ID), AccountMoney(other.AccountMoney) {
    this->name = other.name;
    this->isMale = other.isMale;
    this->userShares = other.userShares;
    this->isWorker = other.isWorker;
}

BankAccount::BankAccount() : ID(IDManager()), AccountMoney(), isMale(false), isWorker(false) {}

BankAccount::BankAccount(IDManager id) : ID(id), isWorker(false), isMale(false) {}

BankAccount::BankAccount(const Money &money, std::string name, bool isMale, bool isWorker) :
        ID(IDManager()), name(std::move(name)), isWorker(isWorker), isMale(isMale) {
    if (money.getValue() < 0) {
        throw Exceptions(NegativeMoney, "\nNegative money was given.\n");
    }
    this->AccountMoney = money;
}

Money BankAccount::getMoney() const {
    return AccountMoney;
}

const std::string &BankAccount::getName() const {
    return name;
}

unsigned int BankAccount::getId() const {
    return ID.getId();
}

void BankAccount::addMoney(const Money &in) {
    this->AccountMoney += in;
}

void BankAccount::subtractMoney(const Money &in) {
    if (this->AccountMoney < in) {
        throw Exceptions(NegativeMoney, "\nThe user does not have enough money to do this.\n");
    }
    this->AccountMoney -= in;
}

std::string BankAccount::getGender() const {
    if (isMale) {
        return {"Male"};
    }
    return {"Female"};
}

[[maybe_unused]] bool BankAccount::getIsWorker() const {
    return isWorker;
}

void BankAccount::BuyShares(Share &SType, int amount) {
    Money priceOfShares = SType.getValue();
    priceOfShares *= amount;

    if (this->AccountMoney < priceOfShares) {
        printf("\nUser does not have enough money.\n");
        return;
    }

    this->subtractMoney(priceOfShares);

    if (!userShares.isEmpty()) {
        for (auto &userShare: userShares) {
            if (userShare.getMasterShareId() == SType.getShareId()) {
                SType.sellToUser(amount, userShare);
                return;
            }
        }
    }

    OwnedShare temp;
    SType.sellToUser(amount, temp);
    if (temp.getMasterShareId() != -1) {
        this->userShares.add_back(temp);
    }
    std::cout << "\nSuccessfully bought the shares!" << std::endl;
}

void BankAccount::SellShares(Share &SType, int amount) {
    if (userShares.isEmpty()) {
        throw Exceptions(NotEnoughShares, "\nTried to sell shares, but didn't buy earlier.\n");
    }
    for (auto i = userShares.begin(); i != userShares.end(); ++i) {
        if ((*i).getMasterShareId() == SType.getShareId()) {

            if (amount <= (*i).getAmount()) { // Mivel a kovetkezo fuggveny nezne ezt meg ezert itt is kell.
                this->addMoney((*i).showValue(&SType)); // Visszaadjuk a penzet a felhasznalonak
            }

            SType.buyFromUser(amount, (*i));

            if ((*i).getAmount() == 0) {
                // The index will never reach a higher number than 100
                // and the instruction set of the processor is 64 bit, so it's safe to static cast the int.
                userShares.pop_index(static_cast<int>(i.distance(userShares.begin())));
            }
            return;
        }
    }
}

void BankAccount::revealShares() {
    for (auto &userShare: userShares) {
        std::cout << userShare << std::endl;
    }
}

bool BankAccount::operator==(const BankAccount &other) {
    return this->ID == other.ID;
}

void BankAccount::loadOShares(const OwnedShare &in) {
    this->userShares.add_back(in);
}

bool BankAccount::getIsMale() const {
    return isMale;
}

TContainer<OwnedShare> &BankAccount::getUserShares() {
    return userShares;
}

void BankAccount::setAccountMoney(const Money &accountMoney) {
    AccountMoney = accountMoney;
}

std::ostream &operator<<(std::ostream &stream, const BankAccount &in) {
    stream << "Name: " << in.getName() << " (id: " << in.getId() << ") " << in.getGender() << " : " << in.getMoney();
    return stream;
}
