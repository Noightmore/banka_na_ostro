#ifndef BACKEND_BANKDATA_HPP
#define BACKEND_BANKDATA_HPP


#include <vector>
#include "UserAccount.hpp"
#include "ExchangeRate.hpp"

namespace bank::models
{
    /**
     * @brief BankData class
     * @details This class is used to represent the data of the bank.
     * @note This class is a singleton.
     */
    class BankData
    {
        private:

                /**
                 * @brief loggedInUsers vector of pointers to UserAccount objects
                 * @details This vector contains all the users that are currently logged in.
                 */
                std::vector<UserAccount*> *loggedInUsers;

                /**
                 * @brief currentExchangeRates vector of pointers to ExchangeRate objects
                 * @details This vector contains all the exchange rates that are currently in use.
                 */
                std::vector<ExchangeRate*> *currentExchangeRates;

                // deletes all the users that are currently logged in
                // called on destruction
                void deleteLoggedInUsers();

                // deletes all the exchange rates that are currently in use
                // called on destruction
                void deleteCurrentExchangeRates();

        public:

                BankData(std::vector<UserAccount*> *loggedInUsers, std::vector<ExchangeRate*> *currentExchangeRates);

                /**
                 * @brief method for creating new instance of BankData class
                 * @return new instance of BankData class
                 */
                static std::unique_ptr<BankData> createInstance();

                void addLoggedInUser(UserAccount *user);

                void removeLoggedInUser(unsigned int id);

                void addCurrentExchangeRate(ExchangeRate *exchangeRate);

                void emptyCurrentExchangeRates();

                std::string& getLoggedInUserInJsonFormat_ById(unsigned int id);

                ~BankData();

    };
}


#endif //BACKEND_BANKDATA_HPP
