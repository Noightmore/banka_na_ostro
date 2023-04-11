#ifndef BACKEND_PAYMENT_HPP
#define BACKEND_PAYMENT_HPP

#include <memory>
#include <boost/date_time.hpp>
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
                // Date of the payment - todo to add
                // the type of payment
                PaymentType* type;
                // the account that is being paid/received from
                 unsigned int* accountId;
                // the amount of money that is being paid/received + currency
                Balance* balance;


        public:
            Payment(std::unique_ptr<unsigned int> id,
                                std::unique_ptr<Balance> balance,
                                std::unique_ptr<unsigned int> accountId,
                                std::unique_ptr<PaymentType> type);

            ~Payment();

            std::string* toString();
        };

}



#endif //BACKEND_PAYMENT_HPP
