#ifndef BANK_VERIFICATIONNOTICEPAGE_HPP
#define BANK_VERIFICATIONNOTICEPAGE_HPP


#include "include/pages/Shared/Page.hpp"

namespace bank::pages
{
    class VerificationNoticePage : public Page
    {
        public:
                void generatePage(std::string& hostIpAddress, std::string& message) override;
    };
}


#endif //BANK_VERIFICATIONNOTICEPAGE_HPP
