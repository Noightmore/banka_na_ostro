#include "../../include/services/SiteFunctionality.hpp"
#include "include/services/BusinessLogic.hpp"
#include "include/pages/LoginPage.hpp"
#include "include/pages/ErrorPage.hpp"
#include "include/pages/UserAccountPage.hpp"
#include "include/pages/VerificationNoticePage.hpp"

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
            pages::VerificationNoticePage verificationPage;


            char* requestMethod = getenv("REQUEST_METHOD");
            char* query_string = std::getenv("QUERY_STRING");

            // set content type
            std::cout << "Content-type:text/html\r\n\r\n";

            if (query_string == nullptr)
            {
                    std::cout << "No query string provided" << std::endl;
            }

            //std::cout << "Query string: " << query_string << std::endl;

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

                    try
                    {
                            data::models::UserAccount user = this->database->getUserAccountById(loginId);
                            // user logged in, print user info
                            userPage.generatePage(this->host_ip_address, message, user); // + loginId
                            return;
                    }
                    catch(std::runtime_error& e)
                    {
                                // user was not found
                                // redirect to login page
                                loginPage.generatePage(this->host_ip_address, message);
                                return;
                    }
            }

            else if (std::strcmp(requestMethod, "POST") == 0)
            {
                if(loginId == -1)
                {
                    // submit form data

                    // check if user exists
                    // send verification email
                    // with a link to user account page
                    try
                    {
                            std::cout << "verification email" << std::endl;
                            // parse form data
                            std::string form_data;
                            getline(std::cin, form_data);

                            // Split the form data into individual fields
                            std::string accountid;
                            char* data = strdup(form_data.c_str());
                            char* field = strtok(data, "&");
                            while (field != NULL)
                            {
                                    std::cout << field << std::endl;
                                    char* name_value = strtok(field, "=");
                                    char* value = strtok(NULL, "=");
                                    if (strcmp(name_value, "id") == 0)
                                    {
                                            accountid = value;
                                    }

                                    field = strtok(NULL, "&");
                            }

                            // parse account id to int
                            int id = std::stoi(accountid);

                            std::cout << "account id: " << id << std::endl;

                            //std::string email = "bitcoin.tul.cz@outlook.com";
                            auto st = verifyUserLogin_ByEmail(id);

                            message = "Verification email sent with status of:" +
                                    std::to_string(static_cast<double>(st));

                            verificationPage.generatePage(this->host_ip_address, message);

                    }
                    catch(std::runtime_error& e)
                    {
                            std::string mess = e.what();
                            errorPage.generatePage(this->host_ip_address, mess);
                    }
                    return;
                }

                // if a user is already logged in, it means we want to generate random payment
                data::models::UserAccount user = this->database->getUserAccountById(loginId);
                //this->generateRandomPayment_ForAccount(loginId);
                userPage.generatePage(this->host_ip_address, message, user);; // + loginId
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

    AuthStatus BusinessLogic::verifyUserLogin_ByEmail(unsigned int userId)
    {
            // check if such user exists = xml file exists
            // if not, throw exception
            std::string email;
            try
            {
                    email = this->database->getUserAccountById(userId).getEmail();
            }

            catch(std::runtime_error& e)
            {
                    throw std::runtime_error("User with id " + std::to_string(userId) + " does not exist.");
            }

            // spawn bash subprocess that deals with email sending
            // we assume emails are already verified at the registration and all users are forced to use outlook

            std::string page_url = "http://" + this->host_ip_address + "/cgi-bin/BankApp.cgi?login=" + std::to_string(userId);

            std::string command =
                    "echo -e \" Subject: Verification\n\nPlease confirm your login here: " + page_url + "\" | msmtp -a outlook " + email + " 2> error.log.txt";

            int status = std::system(command.c_str());

            if (status != 0)
            {
                    // append the contents of error.log and save them as a string

                    std::ifstream file("error.log.txt");

                    if (!file.is_open())
                    {
                            throw std::runtime_error("Error sending email. Error log file could not be opened."
                            + std::to_string(status));
                    }

                    std::string file_contents((std::istreambuf_iterator<char>(file)),
                                              std::istreambuf_iterator<char>());

                    file.close();

                    throw std::runtime_error("Error sending email." + std::to_string(status) + file_contents + "Command: " + command);
            }

            return AuthStatus::AUTHORIZED;
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
}