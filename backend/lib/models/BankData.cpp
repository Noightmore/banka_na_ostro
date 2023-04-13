#include "../../include/models/BankData.hpp"

namespace bank::models
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
}
