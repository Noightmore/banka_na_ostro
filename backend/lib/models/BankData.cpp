#include "../../include/models/BankData.hpp"

namespace bank::models
{
    BankData::BankData(std::vector<UserAccount*> *loggedInUsers)
    {
        this->loggedInUsers = loggedInUsers;
    }

    BankData::~BankData()
    {
        for (auto user : *loggedInUsers)
        {
            delete user;
        }
        delete loggedInUsers;
    }
}
