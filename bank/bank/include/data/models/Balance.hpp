#ifndef BACKEND_BALANCE_HPP
#define BACKEND_BALANCE_HPP

#include <string>
#include <memory>
#include "Money.hpp"

namespace bank::data::models
{
        /**
         * @brief Balance class
         * @details This class is used to represent 1 balance record of a user.
         * @note This class is a child of Money class.
         * amount is the amount of money in the current balance
         */
        class Balance : public Money<std::string, double>
        {
            public:
                Balance(std::string* name, double* amount);
                ~Balance();

            /**
             * @brief method for creating new instance of Balance class
             *
             * @param _name currency name (e.g. USD, EUR, etc.)
             * @param _amount amount of money
             * @return new instance of Balance class
             */
            static std::unique_ptr<Balance> createInstance(std::unique_ptr<std::string> _name,
                                                    std::unique_ptr<double> _amount);

            /**
             * @brief method for converting Balance object to JSON string
             * @return json string representation of Balance object
             */
            std::unique_ptr<std::string> toHtml();
        };
}

#endif //BACKEND_BALANCE_HPP
