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

            // apparently all of the following is not needed because the memory will get freed automatically
            //this->deleteLoggedInUsers();
            // temporary cause memory leak in the program, kernel is going to take care of it anyways...
            //this->deleteCurrentExchangeRates();
            //this->emptyCurrentExchangeRates();

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
                        loggedInUsers->erase(loggedInUsers->begin());
            }
            //delete this->loggedInUsers;

    }

    void BankData::deleteCurrentExchangeRates()
    {
            for (auto exchangeRate : *this->currentExchangeRates)
            {
                    delete exchangeRate;
                    this->currentExchangeRates->erase(this->currentExchangeRates->begin());
            }
            //delete this->currentExchangeRates;
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
                        return;
                }
                index++;
        }
        throw std::invalid_argument("This user is currently not logged in");
    }

    void BankData::addCurrentExchangeRate(std::unique_ptr<ExchangeRate> exchangeRate)
    {
        this->currentExchangeRates->push_back(exchangeRate.release());
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

    unsigned long BankData::getExchangeRateSize() const
    {
            // return amount of exchange rates
            return this->currentExchangeRates->size();
    }

    ExchangeRate& BankData::getRandomExchangeRate_BySeed(unsigned int seed)
    {
                srand(seed);
                auto exCount = this->currentExchangeRates->size();
                int randomIndex = rand() % exCount;
                return *this->currentExchangeRates->at(randomIndex);
    }

    unsigned int BankData::getLoggedInUsersSize() const
    {
            return this->loggedInUsers->size();
    }
}

