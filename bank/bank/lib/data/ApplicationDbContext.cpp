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
            std::string fileName = "../db/" + std::to_string(id) + DOT_XML;
            char* fileNameChar = new char[fileName.length() + 1];
            strcpy(fileNameChar, fileName.c_str());

            xmlDocPtr doc = xmlParseFile(fileNameChar);
            if (doc == nullptr)
            {
                    std::string err = "Failed to find user with id of " + std::to_string(id) + " - invalid Id";
                    throw std::invalid_argument(err);
            }

            xmlNodePtr root = xmlDocGetRootElement(doc);
            for (xmlNodePtr cur = root->children; cur != nullptr; cur = cur->next)
            {
                    if (cur->type == XML_ELEMENT_NODE)
                    {
                            std::cout << cur->name << ": ";
                            xmlChar* content = xmlNodeGetContent(cur);
                            std::cout << content << std::endl;
                            xmlFree(content);
                    }
            }
    }

    void ApplicationDbContext::addPaymentRecordToAUser_ByAccountId(unsigned int id, models::Payment paymentRecord)
    {

    }
}
