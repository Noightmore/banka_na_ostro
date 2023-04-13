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
                // Date of the payment - unix timestamp
                time_t* date;
                // the type of payment
                PaymentType* type;
                // the account that is being paid/received from
                unsigned int* accountId;
                // the amount of money that is being paid/received + currency
                Balance* balance;

                Payment(time_t* date,
                        PaymentType* type,
                        unsigned int* accountId,
                        Balance* balance);
        public:

            // TODO: add static factory method

            ~Payment();

            // not sure if this will be used
            std::string* toString();
        };

}



#endif //BACKEND_PAYMENT_HPP
