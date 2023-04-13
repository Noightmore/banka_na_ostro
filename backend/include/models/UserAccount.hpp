#ifndef BACKEND_USERACCOUNT_HPP
#define BACKEND_USERACCOUNT_HPP

#include <string>
#include <vector>
#include <memory>
#include <regex>

#include "Balance.hpp"
#include "Payment.hpp"

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
            std::vector<Payment*>* payments;

            void deleteBalances();

            void deletePayments();

        public:
            UserAccount(unsigned int* id,
                        std::string* firstName,
                        std::string* lastName,
                        std::string* email,
                        std::string* password,
                        std::vector<Balance*>* balances,
                        std::vector<Payment*>* payments
            );

            std::unique_ptr<UserAccount> static createInstance(std::unique_ptr<unsigned int> id,
                                                               std::unique_ptr<std::string> firstName,
                                                               std::unique_ptr<std::string> lastName,
                                                               std::unique_ptr<std::string> email,
                                                               std::unique_ptr<std::string> password);

            ~UserAccount();

            unsigned int getId();

            void addBalance(std::unique_ptr<Balance> balance);

            void addPayment(std::unique_ptr<Payment> payment);

            bool doPasswordsMatch(std::string& _password);

        };
}

#endif //BACKEND_USERACCOUNT_HPP
