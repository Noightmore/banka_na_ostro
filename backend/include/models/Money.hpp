#ifndef BACKEND_MONEY_HPP
#define BACKEND_MONEY_HPP

#include <string>
#include <memory>

namespace bank::models
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
        class Money // interface
        {
            protected:
                S* name; // name of the currency (USD, EUR, GBP, etc.)
                T* amount; // Amount of money in the balance
            public:
                Money(S* _name, T* _amount);

                std::unique_ptr<Money> static createInstance(std::unique_ptr<S> _name,
                                                              std::unique_ptr<T> _amount);
        };



}

#endif //BACKEND_MONEY_HPP
