#ifndef BACKEND_PAYMENT_HPP
#define BACKEND_PAYMENT_HPP

#include <memory>
#include "Balance.hpp"

namespace bank::data::models
{
        /**
         * @brief Payment class
         * @details This class is used to represent 1 payment record of a user.
         * @note This class is a child of Money class.
         * amount is the amount of money in the used
         */
        class Payment
        {

        private:
                // Date of the payment - unix timestamp
                time_t* date;
                // the type of payment
                std::string* paymentType;
                // the account that is being paid/received from
                unsigned int* accountId;
                // the amount of money that is being paid/received + currency
                Balance* balance;

        public:

            time_t *getDate() const;

            std::string *getPaymentType() const;

            unsigned int *getAccountId() const;

            Balance *getBalance() const;

            Payment(time_t* date,
                    std::string* type,
                    unsigned int* accountId,
                    Balance* balance);

            ~Payment();

            /**
             * @brief method for creating new instance of Payment class
             *
             * @param date the date of the payment
             * @param type if the payment is incoming or outgoing
             * @param accountId the id of the account that is being paid/received from
             * @param balance the amount of money that is being paid/received + the type of the currency
             * @return Payment instance
             */
            static std::unique_ptr<Payment> createInstance(std::unique_ptr<time_t> date,
                                                           std::unique_ptr<std::string> type,
                                                           std::unique_ptr<unsigned int> accountId,
                                                           std::unique_ptr<Balance> balance);

            /**
             * @brief method for formatted printing of the payment
             *
             * @return formatted payment
             */
            std::string& toHtml();

        };

}



#endif //BACKEND_PAYMENT_HPP
