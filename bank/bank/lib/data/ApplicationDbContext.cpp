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
                    // if user has not been loaded to memory, load it from the database
                    this->loadUserFromDatabase_ByAccountId(id);
            }

            // try a second time, if loading user fails the user does not exist
            try
            {
                    return this->bankData->getLoggedInUserAccount_ById(id);
            }
            catch(std::invalid_argument& e)
            {
                    throw std::invalid_argument("User with id " + std::to_string(id) + " does not exist");
            }

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

                    std::cout << cur->name << ": ";
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
                            std::cout << content << std::endl;
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

                std::cout << curr->name << ": ";
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
                std::cout << content2 << std::endl;
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

                    std::cout << curr->name << ": ";
                    xmlChar *content2 = xmlNodeGetContent(curr);
                    if(strcmp((char*)curr->name, "balance_type") == 0)
                    {
                                balanceType = std::string((char*)content2);
                    }
                    else if(strcmp((char*)curr->name, "amount") == 0)
                    {
                                amount = std::stod((char*)content2);
                    }

                    std::cout << content2 << std::endl;
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

                    std::cout << curr->name << ": ";
                    xmlChar *content2 = xmlNodeGetContent(curr);

                    if(strcmp((char*)curr->name, "payment_date") == 0)
                    {
                            paymentDate = reinterpret_cast<time_t> (content2);
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

    [[maybe_unused]]
    void ApplicationDbContext::addPaymentRecordToAUser_ByAccountId(unsigned int id, models::Payment paymentRecord)
    {
            throw std::runtime_error("Not implemented yet");
    }

}