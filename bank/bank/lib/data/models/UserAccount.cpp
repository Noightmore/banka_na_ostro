#include "include/data/models/UserAccount.hpp"
// Path: bank/lib/models/UserAccountPage.cpp

namespace bank::data::models
{
    UserAccount::UserAccount(unsigned int *id, std::string *firstName, std::string *lastName, std::string *email,
                             std::string *password,
                             std::vector<Balance*> *balances,
                             std::vector<Payment*> *payments)
    {
        this->id = id;
        this->firstName = firstName;
        this->lastName = lastName;
        this->email = email;
        this->password = password;
        this->balances = balances;
        this->payments = payments;
    }

    UserAccount::~UserAccount()
    {
        delete this->id;
        delete this->firstName;
        delete this->lastName;
        delete this->email;
        delete this->password;
        this->deleteBalances();
        this->deletePayments();
    }


    unsigned int UserAccount::getId()
    {
        return *this->id;
    }

    void UserAccount::deleteBalances()
    {
        for (auto balance : *this->balances)
        {
            delete balance;
        }
        delete this->balances;
    }

    void UserAccount::deletePayments()
    {
        for(auto payment : *this->payments)
        {
            delete payment;
        }
        delete this->payments;
    }

    bool UserAccount::doPasswordsMatch(std::string& _password)
    {
        if (_password == *this->password)
        {
            return true;
        }
        return false;
    }

    std::unique_ptr<UserAccount>
    UserAccount::createInstance(std::unique_ptr<unsigned int> id, std::unique_ptr<std::string> firstName,
                                std::unique_ptr<std::string> lastName, std::unique_ptr<std::string> email,
                                std::unique_ptr<std::string> password)
    {
        // Check if any of the input parameters are null
        if (!id || !firstName || !lastName || !email || !password)
        {
            throw std::invalid_argument("One or more input parameters are null.");
        }

        // Check if we have read access to the memory
        try
        {
            unsigned int idValue = *id;
            auto len = firstName->length();
            len = lastName->length();
            len = email->length();
            len = password->length();
        }
        catch (std::exception& e)
        {
            throw std::invalid_argument("Read access denied: " + std::string(e.what()));
        }

        // Check if the values of the input parameters are not null
        if (*id == 0 || firstName->empty() || lastName->empty() || email->empty() || password->empty())
        {
            throw std::invalid_argument("One or more input parameter values are null.");
        }

        // check if the values of the input parameters are too long
        if(firstName->length() > 50 || lastName->length() > 50 || email->length() > 50 || password->length() > 50)
        {
            throw std::invalid_argument("One or more input parameter values are too long.");
        }

        // check if email is in valid format
        if (!std::regex_match(*email, std::regex(R"(([a-zA-Z0-9_\-\.]+)@([a-zA-Z0-9_\-\.]+)\.([a-zA-Z]{2,5}))")))
        {
            throw std::invalid_argument("Email is not in valid format.");
        }

        // Create a new instance of UserAccountPage and return it
        return std::make_unique<UserAccount>(id.release(),
                                             firstName.release(),
                                             lastName.release(),
                                             email.release(),
                                             password.release(),
                                             new std::vector<Balance*>(),
                                             new std::vector<Payment*>());
    }

    void UserAccount::addPayment(std::unique_ptr<Payment> payment)
    {
        this->payments->push_back(payment.release());
    }

    void UserAccount::addBalance(std::unique_ptr<Balance> balance)
    {
        this->balances->push_back(balance.release());
    }

    const std::string& UserAccount::getFirstName()
    {
        return *this->firstName;
    }

    const std::string& UserAccount::getLastName()
    {
            return *this->lastName;
    }

    const std::string & UserAccount::getEmail() const {
            return *this->email;
    }

    const std::vector<Balance *> &UserAccount::getBalances()
    {
                return *this->balances;
    }

    const std::vector<Payment *> &UserAccount::getPayments()
    {
                return *this->payments;
    }

    bool UserAccount::doesUserOwnAccount_ForCurrency(std::string &currencyName)
    {
            for (auto& balance : *this->balances)
            {
                    if (balance->getName() == currencyName)
                    {
                            return true;
                    }
            }
            return false;
    }

    bool UserAccount::doesUserHasSufficientFunds_ForCurrency(std::string &currencyName, double amount)
    {
            int index = 0;
            for(auto balance : *this->balances)
            {
                    if (balance->getName() == currencyName)
                    {
                            if (balance->getAmount() - amount >= 0)
                            {
                                    balances->at(index)->setAmount(balance->getAmount() - amount);
                                    return true;
                            }
                    }
                    index++;
            }

            return false;
    }

//    std::string &UserAccountPage::toJson()
//    {
//            auto json = new std::string();
//            json->append("{");
//            json->append("\"id\": " + std::to_string(*this->id) + ",");
//            json->append(R"("firstName": ")" + *this->firstName + "\",");
//            json->append(R"("lastName": ")" + *this->lastName + "\",");
//            json->append(R"("email": ")" + *this->email + "\",");
//            json->append("\"balances\": [");
//            for (auto balance : *this->balances)
//            {
//                    json->append(balance->toJson() + ",");
//            }
//            json->append("],");
//            json->append("\"payments\": [");
//            for (auto payment : *this->payments)
//            {
//                    json->append(payment->toJson() + ",");
//            }
//            json->append("]");
//            json->append("}");
//
//            return *json;
//    }
}