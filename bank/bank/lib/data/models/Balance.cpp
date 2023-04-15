#include "include/data/models/Balance.hpp"

namespace bank::data::models
{

        Balance::Balance(std::string* name, double* amount) : Money()
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
            // check if pointers arent null
            if (_name == nullptr || _amount == nullptr)
            {
                throw std::invalid_argument("Balance::createInstance: one of the arguments is null");
            }

            // check if the amount is negative
            if (_name->empty() || *_amount < 0)
            {
                throw std::invalid_argument("Balance::createInstance: amount cannot be negative");
            }

            return std::make_unique<Balance>(_name.release(), _amount.release());
        }

        std::unique_ptr<std::string> Balance::toJson()
        {
            auto json = new std::string();
            json->append("{");
            json->append(R"("name": ")");
            json->append(*this->name);
            json->append("\",");
            json->append("\"amount\": ");
            json->append(std::to_string(*this->amount));
            json->append("}");

            auto jsonPtr = std::make_unique<std::string>(json->c_str());
            return jsonPtr;
        }
}
