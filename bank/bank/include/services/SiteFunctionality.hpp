#ifndef BACKEND_SITEFUNCTIONALITY_H
#define BACKEND_SITEFUNCTIONALITY_H


#include <memory>
#include "../data/models/UserAccount.hpp"

namespace bank::services
{
    class SiteFunctionality
    {
        virtual data::models::UserAccount loadUserFromDatabase_ById(unsigned int id) = 0;

        virtual std::unique_ptr<std::string> authorizeUserLogin_ByAccountIdAndPassword(unsigned int id,
                                                                                      std::string& password) = 0;

        virtual std::unique_ptr<std::string> verifyUserLogin_ByEmail(std::string& email) = 0;

    };
}


#endif //BACKEND_SITEFUNCTIONALITY_H
