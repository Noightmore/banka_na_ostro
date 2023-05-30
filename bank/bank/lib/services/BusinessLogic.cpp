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
            loginId = this->getParsedUrl(query);

            if (requestMethod == nullptr)
            {
                    std::cerr << "Error getting request method.\n";
                    throw std::runtime_error("Error getting request method.\n");
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
                                //std::cout << "verification email" << std::endl;
                                // parse form data
                                std::string form_data;
                                getline(std::cin, form_data);
                                // Split the form data into individual fields
                                std::string accountid;
                                char* data = strdup(form_data.c_str());
                                char* field = strtok(data, "&");
                                while (field != NULL)
                                {
                                        //std::cout << field << std::endl;
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
                                //std::cout << "account id: " << id << std::endl;
                                //std::string email = "bitcoin.tul.cz@outlook.com";
                                auto st = verifyUserLogin_ByEmail(id);
                                message = "Verification email sent with status of:" +
                                          std::to_string(static_cast<double>(st));
                                verificationPage.generatePage(this->host_ip_address, message);
                        }
                        catch(std::runtime_error& e)
                        {
                                std::string mess = "user does not exist";
                                verificationPage.generatePage(this->host_ip_address, mess);
                        }

                    return;
                }

                // if a user is already logged in, it means we want to generate random payment
                data::models::UserAccount user = this->database->getUserAccountById(loginId);
                user.addPayment(this->generateRandomPayment_ForAccount(user));
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
                    //std::cout << "user id: " << userId << std::endl;
                    email = this->database->getUserAccountById(userId).getEmail();
                    //std::cout << email << std::endl;
                    if (email.empty())
                    {
                            throw std::runtime_error("User with id " + std::to_string(userId) + " does not have an email.");
                    }
            }

            catch(std::runtime_error& e)
            {
                    throw std::runtime_error("User with id " + std::to_string(userId) + " does not exist.");
            }

            // spawn bash subprocess that deals with email sending
            // we assume emails are already verified at the registration and all users are forced to use outlook

            std::string page_url = "http://" + this->host_ip_address +
                    "/cgi-bin/BankApp.cgi?login=" + std::to_string(userId);

            std::string command =
                    "echo -e \" Subject: Verification\n\nPlease confirm your login here: "
                    + page_url + "\" | msmtp -a outlook " + email + " 2> error.log.txt";

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

                    // read file contents of error.log.txt into a string
                    std::string file_contents;
                    file.seekg(0, std::ios::end);
                    file_contents.reserve(file.tellg());
                    file.seekg(0, std::ios::beg);


                    file.close();

                    throw std::runtime_error("Error sending email."
                    + std::to_string(status) + file_contents + "Command: " + command);
            }

            return AuthStatus::AUTHORIZED;
    }

    std::unique_ptr<data::models::Payment>
            BusinessLogic::generateRandomPayment_ForAccount(data::models::UserAccount& user)
    {
        this->database->loadExchangeRates();

        // get random exchange rate
        // get random number

        std::random_device rd;
        std::mt19937 gen(rd());

        // Define the range for the random numbers
        int minNumber = 1;
        int maxNumber = 100;

        std::uniform_int_distribution<> dis(minNumber, maxNumber);

        unsigned int random_num = dis(gen) % 100 + 1;
        data::models::ExchangeRate rate = this->database->bankData->getRandomExchangeRate_BySeed(random_num);

        // get a random account id
        unsigned int random_account_id = random_num;

        // get current linux timestamp
        unsigned int timestamp = static_cast<unsigned int>(std::time(nullptr));


        std::string used_currency = rate.getName();


        // apply random payment for each random exchange rate

        bool isIncoming = dis(gen) % 2 == 0;
        double random_payment_sum = dis(gen) % 1000 + 1;



        if(!user.doesUserOwnAccount_ForCurrency(rate.getName()))
        {
                // convert the currency to czech
                auto prev_val = random_payment_sum;
                random_payment_sum = prev_val * rate.getRate() / rate.getAmount();

                // fifty percent chance for the payment to go into a loan mode (this test only works for user account1)
                if(dis(gen) % 2 == 0)
                {
                        isIncoming = false;

                        if(dis(gen) % 2 == 0)
                        {
                                random_payment_sum = 1101;
                                used_currency = "USD";
                                std::cout << " Attempting to apply usd loan but for way too much " << 1101 << std::endl;
                        }
                        else
                        {
                                random_payment_sum = 10010;

                                // compute prev val
                                prev_val = random_payment_sum * rate.getAmount() / rate.getRate();

                                std::cout << "Converted to CZK amount " << random_payment_sum << " From: " << used_currency << " -- amount " << prev_val << std::endl;
                                used_currency = "CZK";
                        }
                }
                else
                {
                        prev_val = random_payment_sum;
                        random_payment_sum = random_payment_sum * rate.getRate() / rate.getAmount();
                        std::cout << "Converted to CZK amount " << random_payment_sum << " From: " << used_currency << " -- amount " << prev_val << std::endl;
                        used_currency = "CZK";


                }


        }


        // allocate new payment record
        auto balance = data::models::Balance::createInstance(
                std::make_unique<std::string>(used_currency),
                std::make_unique<double>(random_payment_sum)
                );


        auto payment = data::models::Payment::createInstance(
                std::make_unique<time_t>(timestamp),
                std::make_unique<std::string> (isIncoming ? "INCOMING" : "OUTGOING"),
                std::make_unique<unsigned int>(random_account_id),
                std::move(balance)
                );

        // attempt to apply the payment
        if(this->attemptToApplyPayment_ForAccount(user, *payment))
        {

                // if successful, save the payment to the database
                // update the balance amount of the account of the user
                return payment;
        }

        // if attempting to apply the payment was not successful; then we try to apply for a loan
        if(this->attemptToApplyLoan_ForAccount(user, *payment))
        {
                // if successful, save the payment to the database
                // update the balance amount of the account of the user
                return payment;
        }

        // if not successful
        std::cout << "Payment was not successful - insufficient funds." << std::endl;
        // payment gets automatically deleted as its a unique pointer
        return nullptr;
    }


    bool BusinessLogic::attemptToApplyPayment_ForAccount(data::models::UserAccount& account,
                                                         data::models::Payment& payment)
    {
        // check if the user has enough money in the account
        // if not, return false

        // check if the user has the currency of the payment
        // if not, convert the currency to czech and apply the payment

        // if the user has the currency of the payment, apply the payment
        if(*payment.getPaymentType() == "INCOMING")
        {
                account.addFunds(payment.getBalance()->getName(), payment.getBalance()->getAmount());
                return true;
        }


        if(account.doesUserHasSufficientFunds_ForCurrency(payment.getBalance()->getName(),
                                                          payment.getBalance()->getAmount())
                                                          && *payment.getPaymentType() == "OUTGOING")
        {
                return true;
        }

        return false;
    }

    bool
    BusinessLogic::attemptToApplyLoan_ForAccount(data::models::UserAccount &account, data::models::Payment &payment)
    {
        if(account.canUserTakeLoan_ForCurrency(payment.getBalance()->getName(),
                                               payment.getBalance()->getAmount()))
        {
                return true;
        }
        return false;
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