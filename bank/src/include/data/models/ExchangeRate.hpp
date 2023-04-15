#ifndef BACKEND_EXCHANGERATE_HPP
#define BACKEND_EXCHANGERATE_HPP


#include "Money.hpp"

namespace bank::data::models
{
    /**
     * @brief this class represents exchange rate of a chosen currency to CZK currency
     * @details exchange rates are taken from the Czech National Bank site:
     * https://www.cnb.cz/cs/financni-trhy/devizovy-trh/kurzy-devizoveho-trhu/kurzy-devizoveho-trhu/
     */
    class ExchangeRate : public Money<std::string, unsigned int>
    {
        private:
                double* rate;
        public:
                ExchangeRate(std::string* name, unsigned int* amount, double* rate);
                ~ExchangeRate();

                // returns the exchange rate of the currency to CZK
                double getRate();

               /**
               * @brief method for creating new instance of Balance class
               *
               * @param _name currency name (e.g. USD, EUR, etc.)
               * @param _amount default amount of money used to calculate the exchange rate (e.g. 1 USD, 100 YEN, etc.)
               * @return new instance of ExchangeRate class
               */
               static std::unique_ptr<ExchangeRate> createInstance(std::unique_ptr<std::string> _name,
                                                                   std::unique_ptr<unsigned int> _amount,
                                                                   std::unique_ptr<double> _rate);
    };

}

#endif //BACKEND_EXCHANGERATE_HPP
