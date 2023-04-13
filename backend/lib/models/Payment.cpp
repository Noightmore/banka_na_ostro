#include "../../include/models/Payment.hpp"


namespace bank::models
{
    Payment::Payment(time_t *date, bank::models::PaymentType *type, unsigned int *accountId,
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
}
