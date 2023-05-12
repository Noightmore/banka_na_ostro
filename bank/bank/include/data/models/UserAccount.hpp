#ifndef BACKEND_USERACCOUNT_HPP
#define BACKEND_USERACCOUNT_HPP

#include <string>
#include <vector>
#include <memory>
#include <regex>

#include "Balance.hpp"
#include "Payment.hpp"

namespace bank::data::models
{
        /**
         * @brief UserAccountPage class
         * @details This class is used to represent 1 user account.
         * @note This class is a parent of Balance and Payment classes.
         */
        class UserAccount
        {

        private:

            // user id - starting at 1
            unsigned int* id;
            // users' first name
            std::string* firstName;
            // users last name
            std::string* lastName;
            // users email
            std::string* email;
            // users password
            std::string* password;
            // users balances
            std::vector<Balance*>* balances;
            // users payments
            std::vector<Payment*>* payments;

            /**
             * @brief method for deleting balances vector
             * @note this method is used in destructor
             */
            void deleteBalances();

            /**
             * @brief method for deleting payments vector
             * @note this method is used in destructor
             */
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

            /**
            * @brief method for creating new instance of UserAccountPage class
            *
            * @param id user id
            * @param firstName user first name
            * @param lastName user last name
            * @param email user email
            * @param password user password
            * @return new instance of UserAccountPage class
            */
            std::unique_ptr<UserAccount> static createInstance(std::unique_ptr<unsigned int> id,
                                                               std::unique_ptr<std::string> firstName,
                                                               std::unique_ptr<std::string> lastName,
                                                               std::unique_ptr<std::string> email,
                                                               std::unique_ptr<std::string> password);

            ~UserAccount();

            unsigned int getId();

            const std::string& getFirstName();

            const std::string& getLastName();

            const std::string& getEmail();

            const std::vector<Balance*>& getBalances();

            const std::vector<Payment*>& getPayments();


            /**
             * @brief method for adding new balance to balances vector
             * @param balance new balance
             *
             * @param balance new balance object
             */
            void addBalance(std::unique_ptr<Balance> balance);

            /**
             * @brief method for adding new payment to payments vector
             * @param payment new payment object
             */
            void addPayment(std::unique_ptr<Payment> payment);

            /**
             * @brief method for checking whether a given password matches the password of the user
             * @param currencyName currency name
             * @return balance object
             * @note it is very basic
             */
            bool doPasswordsMatch(std::string& _password);

        };
}

#endif //BACKEND_USERACCOUNT_HPP
