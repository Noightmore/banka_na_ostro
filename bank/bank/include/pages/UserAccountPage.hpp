#ifndef BANK_USERACCOUNTPAGE_HPP
#define BANK_USERACCOUNTPAGE_HPP


#include "include/pages/Shared/Page.hpp"

namespace bank::pages
{
    class UserAccountPage : public Page
    {
        public:
            void generatePage(std::string& hostIpAddress, std::string& errorMessage) override;
    };
}


#endif //BANK_USERACCOUNTPAGE_HPP
