#include "../../include/models/UserAccount.hpp"
// Path: backend/lib/models/UserAccount.cpp

namespace bank::models
{

    UserAccount::UserAccount(std::unique_ptr<unsigned int> id,
                             std::unique_ptr<std::string> firstName,
                             std::unique_ptr<std::string> lastName,
                             std::unique_ptr<std::string> email)
    {
        this->id = id.release();
        this->firstName = firstName.release();
        this->lastName = lastName.release();
        this->email = email.release();
        this->balances = new std::vector<Balance*>();

    }

    UserAccount::~UserAccount()
    {
        delete this->id;
        delete this->firstName;
        delete this->lastName;
        delete this->email;
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

}