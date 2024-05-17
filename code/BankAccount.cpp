#include <random>
#include <utility>
#include "../headers/BankAccount.hpp"

BankAccount::BankAccount(const BankAccount &other): ID(other.ID), userMoney(other.userMoney) {
    this->name = other.name;
    this->isMale = other.isMale;
    this->userShares = other.userShares;
    this->isWorker = other.isWorker;
}

BankAccount::BankAccount(): ID(IDManager()), userMoney(), isMale(false), isWorker(false) {}

BankAccount::BankAccount(IDManager id): ID(id), isWorker(false), isMale(false) {}

BankAccount::BankAccount(const Money& money, std::string name, bool isMale, bool isWorker):
        ID(IDManager()), name(std::move(name)), isWorker(isWorker), isMale(isMale)
{
    if (money.getValue() < 0) {
        throw Exceptions(NegativeMoney, "Negative money was given.");
    }
    this->userMoney = money;
}

Money BankAccount::getMoney() const {
    return userMoney;
}

const std::string &BankAccount::getName() const {
    return name;
}

unsigned int BankAccount::getId() const {
    return ID.getId();
}

[[maybe_unused]] void BankAccount::setMoney(const Money& in) {
    this->userMoney = in;
}

[[maybe_unused]] void BankAccount::setName(const std::string &newUserName) {
    this->name = newUserName;
}

void BankAccount::addMoney(const Money &in) {
    this->userMoney += in;
}

void BankAccount::subtractMoney(const Money &in) {
    this->userMoney -= in;
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

[[maybe_unused]] void BankAccount::setIsWorker(bool isWorkerIn) {
    BankAccount::isWorker = isWorkerIn;
}

void BankAccount::BuyShares(Share& SType, int amount) { // Tesztelve, eddig hibatlan
    Money priceOfShares = SType.getValue();
    priceOfShares *= amount;

    if (this->userMoney < priceOfShares) {
        printf("Tesztszoveg, nincs eleg penze :(");
        return;
    }

    this->subtractMoney(priceOfShares);

    if (!userShares.isEmpty()) {
        for (auto & userShare : userShares) {
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
}

void BankAccount::SellShares(Share& SType, int amount) {
    if (userShares.isEmpty()) {
        throw Exceptions(NotEnoughShares, "Tried to sell shares, but didn't buy earlier.");
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
    for (auto & userShare : userShares) {
        std::cout << userShare << std::endl;
    }
}

bool BankAccount::operator==(const BankAccount &other) {
    return this->ID == other.ID;
}

void BankAccount::loadShares(const OwnedShare &in) {
    this->userShares.add_back(in);
}

BankAccount &BankAccount::giveBankReference() {
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const BankAccount& in) {
    stream << "Name: " << in.getName() << " (id: " << in.getId() << ") " << in.getGender() <<" : " << in.getMoney();
    return stream;
}
