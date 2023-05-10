#include "UserAccount.h"

namespace bank::pages
{
    void UserAccount::generatePage(std::string& hostIpAddress, std::string& errorMessage)
    {
        std::cout << "Content-type: text/html\r\n\r\n";
        std::cout << "<html>\n";
        std::cout << "<head>\n";
        std::cout << "<title>Bank</title>\n";
        std::cout << "</head>\n";
        std::cout << "<body>\n";
        std::cout << "<h1>Bank</h1>\n";
        std::cout << "<p>Host IP Address: " << hostIpAddress << "</p>\n";
        std::cout << "<p>Error Message: " << errorMessage << "</p>\n";
        std::cout << "</body>\n";
        std::cout << "</html>\n";
    }
}
