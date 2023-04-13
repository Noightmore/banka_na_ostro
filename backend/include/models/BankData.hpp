#ifndef BACKEND_BANKDATA_HPP
#define BACKEND_BANKDATA_HPP


#include <vector>
#include "UserAccount.hpp"
#include "ExchangeRate.hpp"

namespace bank::models
{
    class BankData
    {
        private:

            std::vector<UserAccount*> *loggedInUsers;
            std::vector<ExchangeRate*> *currentExchangeRates;

            void deleteLoggedInUsers();

            void deleteCurrentExchangeRates();

    public:
            BankData(std::vector<UserAccount*> *loggedInUsers, std::vector<ExchangeRate*> *currentExchangeRates);

            std::unique_ptr<BankData> static createInstance();

            ~BankData();

    };
}

#endif //BACKEND_BANKDATA_HPP
