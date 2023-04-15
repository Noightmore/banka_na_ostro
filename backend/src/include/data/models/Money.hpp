#ifndef BACKEND_MONEY_HPP
#define BACKEND_MONEY_HPP

#include <memory>
#include <string>

namespace bank::data::models
{
    /**
    * @brief Base class for all money related classes
    *
    * @details for any money related classes this provides the name of the currency
    *          example: USD, EUR, GBP, etc.
    *          by default is a string but can be enum or any custom type
    *          and the amount of it - more context is available in the child classes
    *          the type of money can be anything, usually usually double or int or even something custom
    */
    template <typename S, typename T>
    class Money
    {
        protected:
                S* name; // name of the currency (USD, EUR, GBP, etc.)
                T* amount; // Amount of money in the balance
        public:

                // returns the name of the currency
                S& getName();

                // returns the amount of money in the balance/or the default amount which
                // is used to calculate the exchange rate
                T getAmount();
    };

    template<typename S, typename T>
    S& Money<S, T>::getName()
    {
            return *this->name;
    }

    template<typename S, typename T>
    T Money<S, T>::getAmount()
    {
            return *this->amount;
    }

}

#endif //BACKEND_MONEY_HPP
