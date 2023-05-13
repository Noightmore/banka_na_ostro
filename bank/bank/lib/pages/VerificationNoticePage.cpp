#include "include/pages/VerificationNoticePage.hpp"

namespace bank::pages
{
    void VerificationNoticePage::generatePage(std::string &hostIpAddress, std::string &message)
    {
            //std::cout << "Content-Type: text/html\n\n";
            std::cout << "<html lang=\"en\">\n";
            std::cout << "<head>\n";
            std::cout << "<meta charset=\"UTF-8\">\n";
            std::cout << "<title>Bank</title>\n";
            std::cout << "<style>\n";
            std::cout << "body {\n";
            std::cout << "  background-color: #f2f2f2;\n";
            std::cout << "  font-family: Arial, sans-serif;\n";
            std::cout << "}\n";
            std::cout << "h1 {\n";
            std::cout << "  color: #3d3d3d;\n";
            std::cout << "}\n";
            std::cout << "p {\n";
            std::cout << "  font-size: 18px;\n";
            std::cout << "  color: #606060;\n";
            std::cout << "}\n";
            std::cout << "label {\n";
            std::cout << "  display: block;\n";
            std::cout << "  margin-bottom: 10px;\n";
            std::cout << "  color: #3d3d3d;\n";
            std::cout << "}\n";
            std::cout << "input[type=\"text\"] {\n";
            std::cout << "  padding: 10px;\n";
            std::cout << "  font-size: 16px;\n";
            std::cout << "  border: none;\n";
            std::cout << "  border-radius: 5px;\n";
            std::cout << "  background-color: #f9f9f9;\n";
            std::cout << "  box-shadow: inset 1px 1px 3px rgba(0,0,0,0.1);\n";
            std::cout << "}\n";
            std::cout << "input[type=\"submit\"] {\n";
            std::cout << "  background-color: #4CAF50;\n";
            std::cout << "  color: white;\n";
            std::cout << "  padding: 12px 20px;\n";
            std::cout << "  border: none;\n";
            std::cout << "  border-radius: 5px;\n";
            std::cout << "  font-size: 16px;\n";
            std::cout << "  cursor: pointer;\n";
            std::cout << "}\n";
            std::cout << "input[type=\"submit\"]:hover {\n";
            std::cout << "  background-color: #3e8e41;\n";
            std::cout << "}\n";
            std::cout << "</style>\n";
            std::cout << "</head>\n";
            std::cout << "<body>\n";
            std::cout << "<h1>" + message +"</h1>\n";
            std::cout << "</body>\n";
            std::cout << "</html>\n";
    }
}
