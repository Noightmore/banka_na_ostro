#include "include/data/models/BankData.hpp"

namespace bank::data::models
{
    BankData::BankData(std::vector<UserAccount*> *loggedInUsers, std::vector<ExchangeRate*> *currentExchangeRates)
    {
            this->loggedInUsers = loggedInUsers;
            this->currentExchangeRates = currentExchangeRates;
    }

    BankData::~BankData()
    {
            this->deleteLoggedInUsers();
            this->deleteCurrentExchangeRates();
    }

    std::unique_ptr<BankData> BankData::createInstance()
    {
            return std::make_unique<BankData> (
                    new std::vector<UserAccount*>(),
                    new std::vector<ExchangeRate*>());
    }

    void BankData::deleteLoggedInUsers()
    {
            for (auto user : *loggedInUsers)
            {
                    delete user;
            }
            delete this->loggedInUsers;
    }

    void BankData::deleteCurrentExchangeRates()
    {
            for (auto exchangeRate : *currentExchangeRates)
            {
                    delete exchangeRate;
            }
            delete this->currentExchangeRates;
    }

    void BankData::addLoggedInUser(UserAccount *user)
    {
            this->loggedInUsers->push_back(user);
    }

    void BankData::removeLoggedInUser(unsigned int id)
    {
        int index = 0;
        for (auto user : *loggedInUsers)
        {
                if(id == user->getId())
                {
                        delete user;
                        loggedInUsers->erase(loggedInUsers->begin() + index);
                        break;
                }
                index++;
        }
        throw std::invalid_argument("This user is currently not logged in");
    }

    void BankData::addCurrentExchangeRate(ExchangeRate *exchangeRate)
    {
        this->currentExchangeRates->push_back(exchangeRate);
    }

    void BankData::emptyCurrentExchangeRates()
    {
        for(auto rate : *currentExchangeRates)
        {
                delete rate;
        }
        this->currentExchangeRates->clear();
    }

    UserAccount& BankData::getLoggedInUserAccount_ById(unsigned int id)
    {
            for(auto user : *loggedInUsers)
            {
                    if(id == user->getId())
                    {
                            return *user;
                    }
            }

            // return null
            throw std::invalid_argument("This user is currently not logged in");
    }

    ExchangeRate &BankData::getCurrentExchangeRate_ByName(std::string& name)
    {
            for (auto rate : *currentExchangeRates)
            {
                    if(name == rate->getName())
                    {
                            return *rate;
                    }
            }

            throw std::invalid_argument("This exchange rate is currently not in use");
    }

    bool BankData::areExchangeRatesEmpty()
    {
            return currentExchangeRates->empty();
    }



//    std::string &BankData::getLoggedInUserInJsonFormat_ById(unsigned int id)
//    {
//            for (auto user : *loggedInUsers)
//            {
//                    if(id == user->getId())
//                    {
//                            return user->toJson();
//                    }
//
//            }
//            throw std::invalid_argument("This user is currently not logged in");
//    }
}

