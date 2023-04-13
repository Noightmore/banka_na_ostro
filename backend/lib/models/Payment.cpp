#include "../../include/models/Payment.hpp"


namespace bank::models
{
    Payment::Payment(time_t *date, models::PaymentType *type, unsigned int *accountId,
                     bank::models::Balance *balance)
    {
        this->date = date;
        this->type = type;
        this->accountId = accountId;
        this->balance = balance;
    }

    Payment::~Payment()
    {
        delete date;
        delete type;
        delete accountId;
        delete balance;
    }

    std::unique_ptr<Payment>
    Payment::createInstance(std::unique_ptr<time_t> date, std::unique_ptr<PaymentType> type,
                            std::unique_ptr<unsigned int> accountId, std::unique_ptr<Balance> balance)
    {
        // check if any parameter is null
        if(date == nullptr || type == nullptr || accountId == nullptr)
        {
            throw std::invalid_argument("One of the parameters is null");
        }

        // check if the values of the parameters are not null
        // account ids start at 1
        // balance->amount can be 0
        // date cant be 0 or negative
        if(*accountId == 0 || *date == 0)
        {
            throw std::invalid_argument("One of the parameter values is null");
        }

        return std::make_unique<Payment>(date.release(),
                                         type.release(),
                                         accountId.release(),
                                         balance.release());
    }
}
