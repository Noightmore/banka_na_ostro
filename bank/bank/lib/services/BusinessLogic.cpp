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

    void BusinessLogic::run()
    {
        FCGX_Request request;
        FCGX_Init();
        FCGX_InitRequest(&request, 0, 0);
        pages::LoginPage loginPage;
        pages::ErrorPage errorPage;
        loginPage = pages::LoginPage();
        errorPage = pages::ErrorPage();
        std::string message = "";

        // put code here that runs every time the site is accessed via http request
        while (FCGX_Accept_r(&request) == 0)
        {
                const char* method = FCGX_GetParam("REQUEST_METHOD", request.envp);
                const char* uri = FCGX_GetParam("REQUEST_URI", request.envp);

                if (method && std::string(method) == "GET" && uri && std::string(uri) == "/")
                {

                        loginPage.generatePage(this->host_ip_address, message);
                }
                else
                {
                        message = "Error: 404 - Page not found.";
                        errorPage.generatePage(this->host_ip_address, message);
                }
        }
        message = "Error: 404 - Page not found.";
        errorPage.generatePage(this->host_ip_address, message);
//        std::string message = "";
//        pages::LoginPage loginPage;
//        loginPage = pages::LoginPage();
//        loginPage.generatePage(this->host_ip_address, message);
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