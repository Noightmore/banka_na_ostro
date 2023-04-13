#ifndef BACKEND_PAYMENT_HPP
#define BACKEND_PAYMENT_HPP

#include <memory>
#include "Balance.hpp"

namespace bank::models
{
        enum PaymentType
        {
                INCOMING,
                OUTGOING
        };

        class Payment
        {

        private:
                // Date of the payment - unix timestamp
                time_t* date;
                // the type of payment
                PaymentType* type;
                // the account that is being paid/received from
                unsigned int* accountId;
                // the amount of money that is being paid/received + currency
                Balance* balance;

        public:

            Payment(time_t* date,
                    PaymentType* type,
                    unsigned int* accountId,
                    Balance* balance);

            std::unique_ptr<Payment> static createInstance(std::unique_ptr<time_t> date,
                                                           std::unique_ptr<PaymentType> type,
                                                           std::unique_ptr<unsigned int> accountId,
                                                           std::unique_ptr<Balance> balance);

            ~Payment();

            // not sure if this will be used
            std::string* toString();
        };

}



#endif //BACKEND_PAYMENT_HPP
