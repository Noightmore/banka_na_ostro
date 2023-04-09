#ifndef BACKEND_BALANCE_HPP
#define BACKEND_BALANCE_HPP

#include <string>

namespace bank::models
{

        typedef struct
        {
                std::string* name;
                double* amount;
        } Balance;

}

#endif //BACKEND_BALANCE_HPP
