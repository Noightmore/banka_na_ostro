#ifndef BANK_LOGINPAGE_HPP
#define BANK_LOGINPAGE_HPP


#include "include/pages/Shared/Page.hpp"

namespace bank::pages
{
    class LoginPage : public Page
    {
        public:
                void generatePage(std::string& hostIpAddress, std::string& message) override;
    };
}


#endif //BANK_LOGINPAGE_HPP
