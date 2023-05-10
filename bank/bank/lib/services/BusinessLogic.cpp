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

            std::cout << "Content-type: text/html\r\n\r\n";
            std::cout << "<html><head><title>FastCGI C++ Example</title></head>";
            std::cout << "<body><h1>Hello, world!</h1></body></html>";

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