#include "../../include/services/SiteFunctionality.hpp"
#include "include/services/BusinessLogic.hpp"
#include "include/pages/LoginPage.hpp"
#include "include/pages/ErrorPage.hpp"

namespace bank::services
{

    BusinessLogic::BusinessLogic()
    {
        this->database = new data::ApplicationDbContext();
    }

    BusinessLogic::~BusinessLogic()
    {
        delete this->database;
    }

    void BusinessLogic::startup()
    {
        // put startup code here - code that runs only once on the site start
        this->fetchHostIpAddress();
    }

    // notes: all accounts must use czk if we add new payment to the account,
    // and it is not in czk or in any currency the user has, we will convert it to czk
    void BusinessLogic::run()
    {

            char* requestMethod = getenv("REQUEST_METHOD");

            std::cout << "Content-Type: text/html\n\n";
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
            std::cout << "<h1>Welcome To The Bank</h1>\n";
            std::cout << "<p>Please login</p>\n";
            std::cout << "<form action=\"http://" +  this->host_ip_address + PAGE_ROUTE + "\" method=\"post\">\n";
            std::cout << "<label for=\"name\">Name:</label>\n";
            std::cout << "<input type=\"text\" name=\"name\" id=\"name\">\n";
            std::cout << "<label for=\"password\">Password:</label>\n";
            std::cout << "<input type=\"text\" name=\"password\" id=\"password\">\n";
            std::cout << "<input type=\"submit\" value=\"Submit\">\n";
            std::cout << "</form>\n";
            std::cout << "</body>\n";
            std::cout << "</html>\n";

            if (requestMethod == nullptr)
            {
                    std::cerr << "Error getting request method.\n";
                    return;
            }

            if (std::strcmp(requestMethod, "GET") == 0)
            {
                    std::cout << "Content-Type: text/html\n\n";
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
                    std::cout << "<h1>Welcome To The Bank</h1>\n";
                    std::cout << "<p>Please login</p>\n";
                    std::cout << "<form action=\"http://" +  this->host_ip_address + PAGE_ROUTE + "\" method=\"post\">\n";
                    std::cout << "<label for=\"name\">Name:</label>\n";
                    std::cout << "<input type=\"text\" name=\"name\" id=\"name\">\n";
                    std::cout << "<label for=\"password\">Password:</label>\n";
                    std::cout << "<input type=\"text\" name=\"password\" id=\"password\">\n";
                    std::cout << "<input type=\"submit\" value=\"Submit\">\n";
                    std::cout << "</form>\n";
                    std::cout << "</body>\n";
                    std::cout << "</html>\n";
                    return;
            }
    }



    void services::BusinessLogic::fetchHostIpAddress()
    {
            struct ifaddrs *ifap, *ifa;
            struct sockaddr_in *sa;
            char *addr;

            if (getifaddrs(&ifap) == -1)
            {
                    throw std::runtime_error("Error getting network interfaces.");
            }

            for (ifa = ifap; ifa != nullptr; ifa = ifa->ifa_next)
            {
                    if (ifa->ifa_addr->sa_family != AF_INET) continue;

                    sa = (struct sockaddr_in*) ifa->ifa_addr;
                    addr = inet_ntoa(sa->sin_addr);

                    if (std::strcmp(addr, "127.0.0.1") == 0) continue;

                    // found a non-loopback address
                    std::string ip_address(addr);
                    freeifaddrs(ifap);
                    this->host_ip_address = ip_address;
                    return;
            }

            freeifaddrs(ifap);
            throw std::runtime_error("Error finding non-loopback address.");
    }

    const data::models::UserAccount& BusinessLogic::getUserAccount_ById(unsigned int id)
    {
                return this->database->getUserAccountById(id);
    }

    const AuthStatus &BusinessLogic::authorizeUserLogin_ByAccountIdAndPassword(unsigned int id, std::string& password)
    {
            throw std::runtime_error("Not implemented yet.");
    }

    const AuthStatus &BusinessLogic::verifyUserLogin_ByEmail(std::string& email)
    {
            throw std::runtime_error("Not implemented yet.");
    }

}