#include "include/data/ApplicationDbContext.hpp"

namespace bank::data
{

    ApplicationDbContext::ApplicationDbContext()
    {
        bankData = models::BankData::createInstance().release();
    }

    ApplicationDbContext::~ApplicationDbContext()
    {
        delete bankData;
    }

    const models::UserAccount& ApplicationDbContext::getUserAccountById(unsigned int id)
    {
            // check if user has been loaded to memory
            try
            {
                    this->bankData->getLoggedInUserAccount_ById(id);
            }
            catch(std::invalid_argument& e)
            {
                    // if a user has not been loaded to memory, load it from the database
                    // check if user exists in the database
                    // check if file with such id exists
                    std::string fileName = DB_PATH + std::to_string(id) + DOT_XML;
                    std::ifstream file(fileName);
                    if (!file.good())
                    {
                                throw std::invalid_argument("User with id " + std::to_string(id) + " does not exist");
                    }

                    this->loadUserFromDatabase_ByAccountId(id);
            }

            return this->bankData->getLoggedInUserAccount_ById(id);

    }

    void ApplicationDbContext::loadUserFromDatabase_ByAccountId(unsigned int id)
    {
            std::string fileName = DB_PATH + std::to_string(id) + DOT_XML;
            char* fileNameChar = new char[fileName.length() + 1];
            strcpy(fileNameChar, fileName.c_str());

            xmlDocPtr doc = xmlParseFile(fileNameChar);
            if (doc == nullptr)
            {
                    std::string err = "Failed to find user with id of " + std::to_string(id) + " - invalid Id";
                    throw std::invalid_argument(err);
            }

            xmlNodePtr root = xmlDocGetRootElement(doc);

            // loads user from the xml file into memory marking it as logged-in user
            std::unique_ptr<models::UserAccount> user = this->parseUserFromXML(root);
            this->bankData->addLoggedInUser(user.release());

            // returns the user as a reference
            //return this->bankData->getLoggedInUserAccount_ById(id);

    }

    std::unique_ptr<models::UserAccount> ApplicationDbContext::parseUserFromXML(xmlNode *userNode)
    {
            unsigned int id;
            std::string firstName;
            std::string lastName;
            std::string email;
            std::string password;

            std::unique_ptr<models::UserAccount> user_ptr;

            for (xmlNodePtr cur = userNode->children; cur != nullptr; cur = cur->next)
            {
                    if (cur->type != XML_ELEMENT_NODE)
                    {
                                continue;
                    }

                    //std::cout << cur->name << ": ";
                    xmlChar* content = xmlNodeGetContent(cur);


                    if (user_ptr == nullptr)
                    {
                            user_ptr = this->loadBasicUserData(cur,
                                                               content,
                                                               &id,
                                                               &firstName,
                                                               &lastName,
                                                               &email,
                                                               &password);
                            //std::cout << content << std::endl;
                            xmlFree(content);
                            continue;
                    }

                    // load users balances and payment records
                    this->loadUserBalancesAndPaymentRecords(cur, user_ptr.get());


                    xmlFree(content);

            }


            return user_ptr;
    }

    std::unique_ptr<models::UserAccount> ApplicationDbContext::loadBasicUserData(xmlNodePtr cur,
                                                                                 const xmlChar* content,
                                                                                 unsigned int* id,
                                                                                 std::string* firstName,
                                                                                 std::string* lastName,
                                                                                 std::string* email,
                                                                                 std::string* password)
    {
            if(strcmp((char*)cur->name, "account_id") == 0)
            {
                    *id = std::stoi((char*)content);
            }
            else if(strcmp((char*)cur->name, "firstname") == 0)
            {
                    *firstName = (char*)content;
            }
            else if(strcmp((char*)cur->name, "lastname") == 0)
            {
                    *lastName = (char*)content;
            }
            else if(strcmp((char*)cur->name, "email") == 0)
            {
                    *email = (char*)content;
            }
            else if(strcmp((char*)cur->name, "password") == 0)
            {
                    *password = (char*)content;

                    // and password is the last element in the standard user xml file
                    // we create the user to be able to load the rest of the data
                    std::unique_ptr<models::UserAccount> user_ptr;

                    auto _id = std::make_unique<unsigned int> (*id);
                    auto _firstName = std::make_unique<std::string> (*firstName);
                    auto _lastName = std::make_unique<std::string> (*lastName);
                    auto _email = std::make_unique<std::string> (*email);
                    auto _password = std::make_unique<std::string> (*password);

                    user_ptr = models::UserAccount::createInstance(std::move(_id),
                                                                   std::move(_firstName),
                                                                   std::move(_lastName),
                                                                   std::move(_email),
                                                                   std::move(_password));
                    return user_ptr;

            }
            else
            {
                    std::string err = "Corrupted file for user with id of " + std::to_string(*id);
                    throw std::invalid_argument(err);
            }

            return nullptr;
    }

    void ApplicationDbContext::loadUserBalancesAndPaymentRecords(xmlNodePtr cur,
                                                                 models::UserAccount *user)
    {
        for (xmlNodePtr curr = cur->children; curr != nullptr; curr = curr->next)
        {
                if (cur->type != XML_ELEMENT_NODE)
                {
                        continue;
                }

                //std::cout << curr->name << ": ";
                if(strcmp((char*)curr->name, "balance") == 0)
                {
                        std::unique_ptr<models::Balance> balance = this->parseBalanceFromXML(curr);
                        user->addBalance(std::move(balance));
                }
                else if(strcmp((char*)curr->name, "payment") == 0)
                {
                        std::unique_ptr<models::Payment> payment = this->parsePaymentFromXML(curr);
                        user->addPayment(std::move(payment));
                }

                xmlChar *content2 = xmlNodeGetContent(curr);
                //std::cout << content2 << std::endl;
                xmlFree(content2);
        }
    }

    std::unique_ptr<models::Balance> ApplicationDbContext::parseBalanceFromXML(xmlNodePtr bNode)
    {
            std::unique_ptr<models::Balance> balance_ptr;
            std::string balanceType;
            double amount = -1;

            for (xmlNodePtr curr = bNode->children; curr != nullptr; curr = curr->next)
            {
                    if (bNode->type != XML_ELEMENT_NODE)
                    {
                                continue;
                    }

                    //std::cout << curr->name << ": ";
                    xmlChar *content2 = xmlNodeGetContent(curr);
                    if(strcmp((char*)curr->name, "balance_type") == 0)
                    {
                                balanceType = std::string((char*)content2);
                    }
                    else if(strcmp((char*)curr->name, "amount") == 0)
                    {
                                // check if the amount is a valid double
                                if(!std::regex_match((char *) content2, std::regex("^[0-9]+(\\.[0-9]+)?$")))
                                {
                                         return nullptr;
                                }

                                amount = std::stod((char*)content2);
                    }

                    //
                    // std::cout << content2 << std::endl;
                    xmlFree(content2);

                    if (balanceType.empty() || amount == -1)
                    {
                                continue;
                    }

                    auto _balanceType = std::make_unique<std::string> (balanceType);
                    auto _amount = std::make_unique<double> (amount);
                    balance_ptr = models::Balance::createInstance(std::move(_balanceType),
                                                                  std::move(_amount));
                    return balance_ptr;
            }

            return nullptr;
    }

    std::unique_ptr<models::Payment> ApplicationDbContext::parsePaymentFromXML(xmlNodePtr pNode)
    {
            std::unique_ptr<models::Payment> payment_ptr;
            time_t paymentDate = -1;
            std::string paymentType;
            unsigned int payment_receiver_sender_id = -1;
            std::unique_ptr<models::Balance> balance_ptr;
            std::string balanceType;
            double amount = -1;

            for (xmlNodePtr curr = pNode->children; curr != nullptr; curr = curr->next)
            {
                    if (pNode->type != XML_ELEMENT_NODE)
                    {
                            continue;
                    }

                    //std::cout << curr->name << ": ";
                    xmlChar *content2 = xmlNodeGetContent(curr);

                    if(strcmp((char*)curr->name, "payment_date") == 0)
                    {
                            // convert string to time_t
                            paymentDate = std::stoi((char*)content2);
                    }
                    else if(strcmp((char*)curr->name, "payment_type") == 0)
                    {
                            paymentType = std::string((char*)content2);
                    }
                    else if(strcmp((char*)curr->name, "payment_receiver_sender_id") == 0)
                    {
                             payment_receiver_sender_id = std::stoi((char*)content2);
                    }
                    else if(strcmp((char*)curr->name, "payment_currency") == 0)
                    {
                            balanceType = std::string((char*)content2);
                    }
                    else if(strcmp((char*)curr->name, "payment_amount") == 0)
                    {
                            amount = std::stod((char*)content2);
                    }

                    if(balanceType.empty() || amount == -1)
                    {
                            continue;
                    }

                    balance_ptr = models::Balance::createInstance(std::make_unique<std::string>(balanceType),
                                                                  std::make_unique<double>(amount));

                    if(paymentDate == -1 || paymentType.empty() || payment_receiver_sender_id == -1)
                    {
                            continue;
                    }

                    payment_ptr = models::Payment::createInstance(std::make_unique<time_t>(paymentDate),
                                                                  std::make_unique<std::string>(paymentType),
                                                                  std::make_unique<unsigned int>
                                                                          (payment_receiver_sender_id),
                                                                  std::move(balance_ptr));

                    return payment_ptr;
            }
            return nullptr;
    }

//    [[maybe_unused]]
//    void ApplicationDbContext::addPaymentRecordToAUser_ByAccountId(unsigned int id, models::Payment paymentRecord)
//    {
//            throw std::runtime_error("Not implemented yet");
//    }

    void ApplicationDbContext::loadExchangeRates() const
    {
        const std::string url = "https://www.cnb.cz/cs/financni-trhy/devizovy-trh/kurzy-devizoveho-trhu/kurzy-devizoveho-trhu/denni_kurz.txt?date=";
        const std::string cachedFilePath = "denni_kurz.txt";

        // get the current date in the format of dd.mm.yyyy
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        std::stringstream ss;

        ss << std::put_time(&tm, "%d.%m.%Y");

        //std::cout << "<p>" << ss.str() << "</p>" << std::endl;


        // check if file denni_kurz.txt exists in the current directory

        // if not load them from cache,
        // does local cache exist?
        std::ifstream file(cachedFilePath);
        if(file.good())
        {
                // if file exists, then check for potential updates of the cached one
                if(isFileOlderThanOneDay(cachedFilePath.c_str()))
                {
                        DOWNLOAD_FILE_WITH_TIMESTAMP(url + ss.str(), cachedFilePath);
                }
        }
        else
        {
                // if not, download them from the url
                DOWNLOAD_FILE_WITH_TIMESTAMP(url + ss.str(), cachedFilePath);
        }

        // are the exchange rates loaded from the cache file?
        if(!bankData->areExchangeRatesEmpty())
        {
                // if yes, check how old the data are
                if(isFileOlderThanOneDay(cachedFilePath.c_str()))
                {
                        // if older than one day, download new ones
                        DOWNLOAD_FILE_WITH_TIMESTAMP(url + ss.str(), cachedFilePath);
                        // and drop the mem-loaded cache
                        bankData->emptyCurrentExchangeRates();
                }
        }

        // if not or there is an update, load them from the cache file
        loadExchangeRatesFromCacheFile(cachedFilePath);

    }


    bool ApplicationDbContext::isFileOlderThanOneDay(const char* filename)
    {
            struct stat fileInfo{};
            if (stat(filename, &fileInfo) != 0)
            {
                    std::cerr << "Error: failed to get file information for " << filename << std::endl;
                    return false;
            }

            std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::time_t modTime = fileInfo.st_mtime;
            return (now - modTime) > (24 * 60 * 60);  // 1 day = 24 hours * 60 minutes * 60 seconds
    }

    void ApplicationDbContext::loadExchangeRatesFromCacheFile(const std::string& filename) const
    {
            std::ifstream file(filename);

            if (!file.is_open())
            {
                    throw std::runtime_error("Failed to open file: " + filename);
            }

            std::string line;
            // skip the header line and the second line
            std::getline(file, line);
            std::getline(file, line);

            while (std::getline(file, line))
            {
                    std::istringstream iss(line);
                    std::unique_ptr<std::string> currencyCodePtr = std::make_unique<std::string>();
                    unsigned int amount;
                    char delimiter = '|' ;
                    double rate;


                    // split line with delimiter
                    std::vector<std::string> tokens;
                    std::string token;
                    while(std::getline(iss, token, delimiter))
                    {
                            tokens.push_back(token);
                    }

                    try
                    {
                                //name = tokens.at(0);
                                // copy token.at(3) into currencyCode
                                currencyCodePtr->assign(tokens.at(3));
                                amount = std::stoi(tokens.at(2));

                                // replace comma with dot
                                std::size_t pos = tokens.at(4).find(',');
                                tokens.at(4).replace(pos, 1, ".");

                                rate = std::stod(tokens.at(4));
                    }
                    catch (std::exception& e)
                    {
                                std::string error = "Failed to parse line: " + line;
                                error += "\n";
                                error += "in file " + filename;
                                error += "\n";
                                error += "corrupted or missing data";
                                error += "\n";
                                error += *currencyCodePtr + " "
                                        + std::to_string(amount) + " " + std::to_string(rate);

                                throw std::runtime_error(error);
                    }

                    // turn stack allocated variable currency code into heap allocated and pass it as a unique_ptr

                    auto exchangeRate = bank::data::models::ExchangeRate::createInstance(
                            std::move(currencyCodePtr),
                            std::make_unique<unsigned int>(amount),
                            std::make_unique<double>(rate)
                    );

                    // print the contents of each exchange rate
//                    std::cout << exchangeRate->getName() <<std::endl;
//                    std::cout << exchangeRate->getAmount() <<std::endl;
//                    std::cout << exchangeRate->getRate() <<std::endl;
                    this->bankData->addCurrentExchangeRate(std::move(exchangeRate));

            }

            file.close();
    }

}