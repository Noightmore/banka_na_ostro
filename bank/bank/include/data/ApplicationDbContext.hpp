#ifndef BACKEND_APPLICATIONDBCONTEXT_HPP
#define BACKEND_APPLICATIONDBCONTEXT_HPP

#include <libxml/parser.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>


#include "include/data/models/BankData.hpp"

#define DB_PATH ("../db/")
#define DOT_XML (".xml")

#define DOWNLOAD_FILE_WITH_TIMESTAMP(url, file_path) \
    do { \
        std::string command = "wget -O " + file_path + " " + url; \
        std::system(command.c_str()); \
    } while (0)




namespace bank::data
{
    /**
     * @brief The main class for the database context
     *
     * @details this class is managing all read and write operations to the database
     *          in this case it is a simple xml file local database located in the bank/db directory
     *          also provides the bank data to the whole application
     */
    class ApplicationDbContext
    {
        private:
                models::BankData *bankData;

                // series of helper methods for loading and parsing user data from the database
                std::unique_ptr<models::UserAccount> parseUserFromXML(xmlNode *userNode);

                std::unique_ptr<models::UserAccount>
                loadBasicUserData(xmlNodePtr cur, const xmlChar *content, unsigned int* id, std::string* firstName,
                                std::string* lastName,
                                std::string* email, std::string* password);

                void loadUserBalancesAndPaymentRecords(xmlNodePtr cur,  models::UserAccount* user);

                /**
                * @brief method for loading a single user from the database by his account id
                *
                * @param id account id
                * @return reference to the user object
                */
                void loadUserFromDatabase_ByAccountId(unsigned int id);


                // does exactly what the name implies
                static bool isFileOlderThanOneDay(const char* filename);


        public:
            ApplicationDbContext();
            ~ApplicationDbContext();


            const models::UserAccount& getUserAccountById(unsigned int id);


            [[maybe_unused]] void addPaymentRecordToAUser_ByAccountId(unsigned int id, models::Payment paymentRecord);

            std::unique_ptr<models::Balance> parseBalanceFromXML(xmlNodePtr bNode);

            std::unique_ptr<models::Payment> parsePaymentFromXML(xmlNodePtr pNode);

            // method that downloads the exchange rates from url (only in specific time), in the form of a text file
            // and parses the data into a vector of ExchangeRate objects
            void loadExchangeRates();
    };
}


#endif //BACKEND_APPLICATIONDBCONTEXT_HPP
