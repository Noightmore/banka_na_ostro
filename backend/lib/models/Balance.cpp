#include "../../include/models/Balance.hpp"

namespace bank::models
{

        Balance::Balance() : Money<std::string, double>()
        {
            this->name = name;
            this->amount = amount;
        }

        Balance::~Balance()
        {
            delete this->name;
            delete this->amount;
        }

    std::unique_ptr<Balance>
    Balance::createInstance(std::unique_ptr<std::string> _name, std::unique_ptr<double> _amount)
    {

    }

}
