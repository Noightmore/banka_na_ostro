#ifndef BANK_PAGE_HPP
#define BANK_PAGE_HPP

#include <string>
#include <iostream>

#define PAGE_ROUTE "/cgi-bin/BankApp.cgi"

namespace bank::pages
{
    class Page
    {
        public:
            // method for generating a page
            virtual void generatePage(std::string& hostIpAddress, std::string& message) = 0;
    };
}

#endif //BANK_PAGE_HPP
