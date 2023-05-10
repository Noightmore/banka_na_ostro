#ifndef BANK_ERRORPAGE_HPP
#define BANK_ERRORPAGE_HPP


#include <string>

#include "include/pages/Shared/Page.hpp"

namespace bank::pages
{
    class ErrorPage : public Page
    {
        public:
            void generatePage(std::string& hostIpAddress, std::string& errorMessage) override;
    };
}


#endif //BANK_ERRORPAGE_HPP
