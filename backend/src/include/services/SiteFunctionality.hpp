#ifndef BACKEND_SITEFUNCTIONALITY_H
#define BACKEND_SITEFUNCTIONALITY_H


#include <memory>
#include "../data/models/UserAccount.hpp"

namespace bank::services
{
    class SiteFunctionality
    {
        virtual std::unique_ptr<models::UserAccount> loadUserFromDatabaseById(unsigned int id) = 0;

        virtual std::unique_ptr<std::string> authorizeUserLoginByAccountIdAndPassword(unsigned int id,
                                                                                      std::string& password) = 0;

        virtual std::unique_ptr<std::string> verifyUserLoginByEmail(std::string& email) = 0;

    };
}


#endif //BACKEND_SITEFUNCTIONALITY_H
