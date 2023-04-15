#include "include/data/models/Payment.hpp"


namespace bank::data::models
{
    Payment::Payment(time_t *date, std::string *type, unsigned int *accountId,
                     Balance *balance)
    {
        this->date = date;
        this->paymentType = type;
        this->accountId = accountId;
        this->balance = balance;
    }

    Payment::~Payment()
    {
        delete date;
        delete paymentType;
        delete accountId;
        delete balance;
    }

    std::unique_ptr<Payment>
    Payment::createInstance(std::unique_ptr<time_t> date, std::unique_ptr<std::string> type,
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

//    std::string &Payment::toJson()
//    {
//        auto *json = new std::string();
//        json->append("{");
//        json->append("\"date\":");
//        json->append(std::to_string(*date));
//        json->append(",");
//        json->append("\"type\":");
//        json->append("\"");
//        json->append(*paymentType);
//        json->append("\"");
//        json->append(",");
//        json->append("\"accountId\":");
//        json->append(std::to_string(*accountId));
//        json->append(",");
//        json->append("\"balance\":");
//        json->append(balance->toJson());
//        json->append("}");
//        return *json;
//    }
}
