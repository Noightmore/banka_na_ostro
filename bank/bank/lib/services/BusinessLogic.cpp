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
            std::string message = "";
            pages::LoginPage loginPage;
            pages::ErrorPage errorPage;

            char* requestMethod = getenv("REQUEST_METHOD");
            char* query_string = std::getenv("QUERY_STRING");

            std::cout << "Content-type:text/html\r\n\r\n";

            if (query_string == nullptr)
            {
                    std::cout << "No query string provided" << std::endl;
            }

            std::cout << "Query string: " << query_string << std::endl;

            // TODO: implement query string parser

            if (requestMethod == nullptr)
            {
                    std::cerr << "Error getting request method.\n";
                    return;
            }

            if (std::strcmp(requestMethod, "GET") == 0)
            {
                    loginPage.generatePage(this->host_ip_address, message);
                    return;
            }

            else if (std::strcmp(requestMethod, "POST") == 0)
            {
                    return;
            }

            //message = query_string;
            errorPage.generatePage(this->host_ip_address, message);
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

    const AuthStatus &BusinessLogic::verifyUserLogin_ByEmail(std::string& email)
    {
            throw std::runtime_error("Not implemented yet.");
    }

    void BusinessLogic::generateRandomPayment_ForAccount(unsigned int id)
    {
        throw std::runtime_error("Not implemented yet.");
    }

    std::string &BusinessLogic::getParsedUrl(std::string &query)
    {
        throw std::runtime_error("Not implemented yet.");
    }

}