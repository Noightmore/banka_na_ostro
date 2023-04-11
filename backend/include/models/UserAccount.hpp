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
            std::vector<Balance*>* balances;


            void deleteBalances();

        public:
            UserAccount(std::unique_ptr<unsigned int> id,
                        std::unique_ptr<std::string> firstName,
                        std::unique_ptr<std::string> lastName,
                        std::unique_ptr<std::string> email);

            ~UserAccount();

            unsigned int getId();

            void addBalance(std::unique_ptr<std::string> currency, std::unique_ptr<double> amount);
        };
}

#endif //BACKEND_USERACCOUNT_HPP
