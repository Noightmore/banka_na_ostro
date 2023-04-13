#ifndef BACKEND_USERACCOUNT_HPP
#define BACKEND_USERACCOUNT_HPP

#include <string>
#include <vector>
#include <memory>
#include "Balance.hpp"

namespace bank::models
{
        class UserAccount
        {

        private:

            unsigned int* id;
            std::string* firstName;
            std::string* lastName;
            std::string* email;
            std::string* password;
            std::vector<Balance*>* balances;

            UserAccount(unsigned int* id,
                        std::string* firstName,
                        std::string* lastName,
                        std::string* email,
                        std::string* password,
                        std::vector<Balance*>* balances);

            void deleteBalances();

        public:

            // TODO: add static factory method

            ~UserAccount();

            unsigned int getId();

            void addBalance(std::unique_ptr<std::string> currency, std::unique_ptr<double> amount);

            bool doPasswordsMatch(std::string& _password);
        };
}

#endif //BACKEND_USERACCOUNT_HPP
