#include "include/pages/ErrorPage.hpp"

namespace bank::pages
{

    void ErrorPage::generatePage(std::string &hostIpAddress, std::string &errorMessage)
    {
            //std::cout << "Content-type:text/html\r\n\r\n";
            std::cout << "<!DOCTYPE html>\n";
            std::cout << "<html lang=\"en\">\n";
            std::cout << "<head>\n";
            std::cout << "<meta charset=\"UTF-8\">\n";
            std::cout << "<title>Error Page</title>\n";
            std::cout << "<style>\n";
            std::cout << "body {\n";
            std::cout << "    background-color: #f2f2f2;\n";
            std::cout << "}\n";
            std::cout << "h1 {\n";
            std::cout << "    color: #333333;\n";
            std::cout << "    text-align: center;\n";
            std::cout << "    margin-top: 100px;\n";
            std::cout << "}\n";
            std::cout << "p {\n";
            std::cout << "    color: #666666;\n";
            std::cout << "    text-align: center;\n";
            std::cout << "    font-size: 16px;\n";
            std::cout << "}\n";
            std::cout << "</style>\n";
            std::cout << "</head>\n";
            std::cout << "<body>\n";
            std::cout << "<h1>Oops! Something went wrong.</h1>\n";
            std::cout << "<p>"+ errorMessage +"</p>\n";
            std::cout << "</body>\n";
            std::cout << "</html>\n";
    }
}

