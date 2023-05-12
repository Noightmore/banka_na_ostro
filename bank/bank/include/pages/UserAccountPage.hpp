#ifndef BANK_USERACCOUNTPAGE_HPP
#define BANK_USERACCOUNTPAGE_HPP


#include "include/pages/Shared/Page.hpp"
#include "include/data/models/UserAccount.hpp"

namespace bank::pages
{
    class UserAccountPage : public Page
    {
        public:
            void generatePage(std::string& hostIpAddress, std::string& errorMessage, data::models::UserAccount& userAccount);

            void generatePage(std::string& hostIpAddress, std::string& errorMessage) override;

            void generateUserData(bank::data::models::UserAccount& userAccount);
    };
}


#endif //BANK_USERACCOUNTPAGE_HPP
