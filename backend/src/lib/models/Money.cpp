#include "../../include/models/Money.hpp"

namespace bank::models
{
    template<typename S, typename T>
    Money<S, T>::Money(S *_name, T *_amount)
    {

    }

    template <typename S, typename T>
    std::unique_ptr<Money<S, T>> Money<S, T>::createInstance(std::unique_ptr<S> _name, std::unique_ptr<T> _amount)
    {
            // check if pointers arent null
            if (_name == nullptr || _amount == nullptr)
            {
                    throw std::invalid_argument("one of the arguments is null");
            }

            // check if the amount is negative
            if (*_amount < 0)
            {
                    throw std::invalid_argument("amount cannot be negative");
            }

            return std::make_unique<Money<S,T>>(_name.release(), _amount.release());
    }
}
