#include "../../include/models/UserAccount.hpp"
// Path: backend/lib/models/UserAccount.cpp

namespace bank::models
{
    UserAccount::UserAccount(unsigned int *id, std::string *firstName, std::string *lastName, std::string *email,
                             std::string *password,
                             std::vector<Balance*> *balances)
    {
        this->id = id;
        this->firstName = firstName;
        this->lastName = lastName;
        this->email = email;
        this->password = password;
        this->balances = balances;
    }

    UserAccount::~UserAccount()
    {
        delete this->id;
        delete this->firstName;
        delete this->lastName;
        delete this->email;
        delete this->password;
        this->deleteBalances();
    }


    unsigned int UserAccount::getId()
    {
        return *this->id;
    }

    void UserAccount::addBalance(std::unique_ptr<std::string> currency, std::unique_ptr<double> amount)
    {
        this->balances->push_back(new Balance(currency.release(), amount.release()));
    }

    void UserAccount::deleteBalances()
    {
        for (auto balance : *this->balances)
        {
            delete balance->name;
            delete balance->amount;
            delete balance;
        }
        delete this->balances;
    }

    bool UserAccount::doPasswordsMatch(std::string& _password)
    {
        if (_password == *this->password)
        {
            return true;
        }
        return false;
    }
}