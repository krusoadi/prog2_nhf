#include <random>
#include <utility>
#include "../headers/BankAccount.hpp"

BankAccount::BankAccount(const BankAccount &other): ID(other.ID), userMoney(other.userMoney) {
    this->name = other.name;
    this->isMale = other.isMale;
    this->userShares = other.userShares;
    this->isWorker = other.isWorker;
}

BankAccount::BankAccount(): ID(BankAccount::getGeneratedID()), userMoney(), isMale(false), isWorker(false) {}

BankAccount::BankAccount(const Money& money, std::string name, bool isMale, bool isWorker):
        ID(BankAccount::getGeneratedID()), name(std::move(name)), isWorker(isWorker), isMale(isMale)
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
    return ID;
}

void BankAccount::setMoney(const Money& in) {
    this->userMoney = in;
}

int BankAccount::getGeneratedID() {

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

void BankAccount::subtractMoney(const Money &in) {
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

void BankAccount::BuyShares(Share& Stype, int amount) { // Tesztelve, eddig hibatlan
    Money priceOfShares = Stype.getValue();
    priceOfShares *= amount;

    if (this->userMoney < priceOfShares) {
        printf("Tesztszoveg, nincs eleg penze :(");
        return;
    }

    this->subtractMoney(priceOfShares);

    if (!userShares.isEmpty()) {
        for (auto & userShare : userShares) {
            if (userShare.getMasterShareId() == Stype.getShareId()) {
                Stype.sellToUser(amount, userShare);
                return;
            }
        }
    }

    OwnedShare temp;
    Stype.sellToUser(amount, temp);
    if (temp.getMasterShareId() != -1) {
        this->userShares.add_back(temp);
    }
}

void BankAccount::SellShares(Share& type, int amount) {
    if (!userShares.isEmpty()) {
        for (auto i = userShares.begin(); i != userShares.end(); ++i) {
            if ((*i).getMasterShareId() == type.getShareId()) {

                if (amount <= (*i).getAmount()) { // Mivela kovetkezo fuggveny nezne ezt meg ezert itt is kell.
                    this->addMoney((*i).showValue(&type)); // Visszaadjuk a penzet a felhasznalonak
                }

                type.buyFromUser(amount, (*i));

                if ((*i).getAmount() == 0) {
                    userShares.pop_index(static_cast<int>(i.distance(userShares.begin()))); // TODO could be unsafe??
                }
                return;
            }
        }
    }
    throw Exceptions(NotEnoughShares, "Tried to sell shares, but didn't buy earlier. (empty user)");
}

void BankAccount::revealShares() {
    for (auto & userShare : userShares) {
        std::cout << userShare << std::endl;
    }
}

std::ostream& operator<<(std::ostream& stream, const BankAccount& in) {
    stream << "Name: " << in.getName() << " (id: " << in.getId() << ") " << in.getGender() <<" : " << in.getMoney();
    return stream;
}
