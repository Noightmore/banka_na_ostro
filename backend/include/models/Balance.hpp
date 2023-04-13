#ifndef BACKEND_BALANCE_HPP
#define BACKEND_BALANCE_HPP

#include <string>
#include <memory>
#include "Money.hpp"

namespace bank::models
{

        class Balance : public Money
        {
            private:
                double* amount;

            public:
                Balance(std::string* name, double* amount);
                ~Balance();

                std::unique_ptr<Balance> createInstance(std::unique_ptr<std::string> _name,
                                                        std::unique_ptr<double> _amount);
        };

}

#endif //BACKEND_BALANCE_HPP
