#ifndef BANK_USERACCOUNT_H
#define BANK_USERACCOUNT_H


#include "include/pages/Shared/Page.hpp"

namespace bank::pages
{
    class UserAccount : public Page
    {
        public:
            void generatePage(std::string& hostIpAddress, std::string& errorMessage) override;
    };
}


#endif //BANK_USERACCOUNT_H
