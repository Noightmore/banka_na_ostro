#ifndef BACKEND_EXCHANGERATE_HPP
#define BACKEND_EXCHANGERATE_HPP


#include "Money.hpp"

namespace bank::models
{
    class ExchangeRate : public Money
    {
        // https://www.cnb.cz/cs/financni-trhy/devizovy-trh/kurzy-devizoveho-trhu/kurzy-devizoveho-trhu/
        std::string* countryName;
        unsigned int* amount;
        double* rate;
    };
}

#endif //BACKEND_EXCHANGERATE_HPP
