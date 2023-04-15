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
            std::unique_ptr<models::UserAccount> user = this->parseUserFromXML(root);
            this->bankData->addLoggedInUser(user.release());

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
                    if (cur->type == XML_ELEMENT_NODE)
                    {
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
                            this->loadUserBalancesAndPaymentRecords(cur, content, user_ptr.get());


                            xmlFree(content);

                    }
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

    void ApplicationDbContext::loadUserBalancesAndPaymentRecords(xmlNodePtr cur, const xmlChar *content,
                                                                 models::UserAccount *user)
    {
        for (xmlNodePtr curr = cur->children; curr != nullptr; curr = curr->next)
        {
                if (cur->type == XML_ELEMENT_NODE)
                {
                        std::cout << curr->name << ": ";
                        if(strcmp((char*)curr->name, "balance") == 0)
                        {
                                user->addBalance(this->parseBalanceFromXML(curr));
                        }
                        xmlChar *content2 = xmlNodeGetContent(curr);
                        std::cout << content2 << std::endl;
                        xmlFree(content2);
                }
        }
    }

    std::unique_ptr<models::Balance> ApplicationDbContext::parseBalanceFromXML(xmlNodePtr cur)
    {
            std::unique_ptr<models::Balance> balance_ptr;
            std::string balanceType;
            double amount = -1;

            for (xmlNodePtr curr = cur->children; curr != nullptr; curr = curr->next)
            {
                    if (cur->type == XML_ELEMENT_NODE)
                    {
                            std::cout << curr->name << ": ";
                            xmlChar *content2 = xmlNodeGetContent(curr);
                            if(strcmp((char*)curr->name, "balance_type") == 0)
                            {
                                        balanceType = (char*)content2;
                            }
                            else if(strcmp((char*)curr->name, "amount") == 0)
                            {
                                        amount = std::stod((char*)content2);
                            }

                            std::cout << content2 << std::endl;
                            xmlFree(content2);

                            if(!balanceType.empty() && amount != -1)
                            {
                                    auto _balanceType = std::make_unique<std::string> (balanceType);
                                    auto _amount = std::make_unique<double> (amount);
                                    balance_ptr = models::Balance::createInstance(std::move(_balanceType),
                                                                                  std::move(_amount));
                                    return balance_ptr;
                            }
                    }
            }
    }

    [[maybe_unused]]
    void ApplicationDbContext::addPaymentRecordToAUser_ByAccountId(unsigned int id, models::Payment paymentRecord)
    {
            throw std::runtime_error("Not implemented yet");
    }



}