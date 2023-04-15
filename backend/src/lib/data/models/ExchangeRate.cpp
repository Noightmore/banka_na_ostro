#include "include/data/models/ExchangeRate.hpp"

namespace bank::data::models
{

    ExchangeRate::ExchangeRate(std::string *name, unsigned int *amount, double *rate) : Money()
    {
        this->name = name;
        this->amount = amount;
        this->rate = rate;
    }

    ExchangeRate::~ExchangeRate()
    {
        delete this->name;
        delete this->amount;
        delete this->rate;
    }

    std::unique_ptr<ExchangeRate>
    ExchangeRate::createInstance(std::unique_ptr<std::string> _name, std::unique_ptr<unsigned int> _amount,
                                 std::unique_ptr<double> _rate)
    {
            // check if any parameter is null
            if(_name == nullptr || _amount == nullptr || _rate == nullptr)
            {
                    throw std::invalid_argument("One of the parameters is null");
            }

            // check if the values of the parameters are not null
            if(_name->empty() || *_amount == 0 || *_rate == 0)
            {
                    throw std::invalid_argument("One of the parameter values is null");
            }

            return std::make_unique<ExchangeRate>(_name.release(),
                                                  _amount.release(),
                                                  _rate.release());
    }

    double ExchangeRate::getRate()
    {
            return *this->rate;
    }

}