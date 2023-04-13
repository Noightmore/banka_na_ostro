#ifndef BACKEND_EXCHANGERATE_HPP
#define BACKEND_EXCHANGERATE_HPP


#include "Money.hpp"

namespace bank::models
{
    /**
     * @brief this class represents exchange rate of a chosen currency to CZK currency
     * @details exchange rates are taken from the Czech National Bank site:
     * https://www.cnb.cz/cs/financni-trhy/devizovy-trh/kurzy-devizoveho-trhu/kurzy-devizoveho-trhu/
     */
    class ExchangeRate : public Money<unsigned int>
    {

        private:
                double* rate;

        public:

    };
}

#endif //BACKEND_EXCHANGERATE_HPP
