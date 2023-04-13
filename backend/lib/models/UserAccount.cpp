#include <regex>
#include "../../include/models/UserAccount.hpp"
// Path: backend/lib/models/UserAccount.cpp

namespace bank::models
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
            delete balance->name;
            delete balance->amount;
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

        // Create a new instance of UserAccount and return it
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

    void UserAccount::addBalance(std::unique_ptr<std::string> currency, std::unique_ptr<double> amount)
    {
        this->balances->push_back(new Balance(currency.release(), amount.release()));
    }
}