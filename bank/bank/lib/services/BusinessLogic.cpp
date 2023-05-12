#include "../../include/services/SiteFunctionality.hpp"
#include "include/services/BusinessLogic.hpp"
#include "include/pages/LoginPage.hpp"
#include "include/pages/ErrorPage.hpp"
#include "include/pages/UserAccountPage.hpp"

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
            int loginId = -1;
            pages::LoginPage loginPage;
            pages::UserAccountPage userPage;
            pages::ErrorPage errorPage;

            char* requestMethod = getenv("REQUEST_METHOD");
            char* query_string = std::getenv("QUERY_STRING");

            // set content type
            std::cout << "Content-type:text/html\r\n\r\n";

            if (query_string == nullptr)
            {
                    std::cout << "No query string provided" << std::endl;
            }

            std::cout << "Query string: " << query_string << std::endl;

            std::string query = std::string(query_string);
            loginId= this->getParsedUrl(query);

            if (requestMethod == nullptr)
            {
                    std::cerr << "Error getting request method.\n";
                    return;
            }

            if (std::strcmp(requestMethod, "GET") == 0)
            {
                    if(loginId == -1)
                    {
                        loginPage.generatePage(this->host_ip_address, message);
                        return;
                    }

                    // user logged in, print user info
                    userPage.generatePage(this->host_ip_address, message); // + loginId
                    return;
            }

            else if (std::strcmp(requestMethod, "POST") == 0)
            {
                if(loginId == -1)
                {
                    // submit form data
                    // check if user exists
                    // send verification email
                    // with a link to user account page
                    return;
                }

                // if a user is already logged in, it means we want to generate random payment
                this->generateRandomPayment_ForAccount(loginId);
                userPage.generatePage(this->host_ip_address, message); // + loginId
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

    int BusinessLogic::getParsedUrl(std::string& query)
    {
            // check if delimiter is present and not at the beginning or end of the string
            std::string delimiter = "=";
            size_t delimiterPos = query.find(delimiter);

            if (delimiterPos == std::string::npos || delimiterPos == 0
            || delimiterPos == query.size() - delimiter.length())
            {
                    throw std::invalid_argument("Invalid query string: missing or misplaced delimiter");
            }

            // extract token after delimiter and convert to int
            std::string token = query.substr(delimiterPos + delimiter.length());
            return std::stoi(token);
    }


    std::vector<data::models::ExchangeRate> &BusinessLogic::getExchangeRates()
    {
        throw std::runtime_error("Not implemented yet.");
    }

}