#ifndef BACKEND_SITEFUNCTIONALITY_H
#define BACKEND_SITEFUNCTIONALITY_H

#include <cstring>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <string>
#include <cstdlib>
#include <memory>
#include <thread>
#include <fstream>
#include <curl/curl.h>

#include "AuthStatus.h"
#include "../data/models/UserAccount.hpp"
#include "include/data/models/ExchangeRate.hpp"

namespace bank::services
{
    class SiteFunctionality
    {
        protected:
                virtual void fetchHostIpAddress() = 0;

                virtual const data::models::UserAccount& getUserAccount_ById(unsigned int id) = 0;

                //virtual const AuthStatus& authorizeUserLogin_ByAccountIdAndPassword(unsigned int id,
                //                                                                   std::string& password) = 0;

                virtual const AuthStatus& verifyUserLogin_ByEmail(std::string& email) = 0;

                virtual void generateRandomPayment_ForAccount(unsigned int id) = 0;

                // url is entered in the following format:
                // login=loginId
                // loginId is the id of the user account
                // -1 is returned if no user is logged in
                virtual int getParsedUrl(std::string& query) = 0;

                // method that downloads the exchange rates from url (only in specific time), in a form of a text file
                // and parses the data into a vector of ExchangeRate objects
                virtual std::vector<data::models::ExchangeRate>& getExchangeRates() = 0;

        public:
                virtual void run() = 0;

                virtual void startup() = 0;
    };
}


#endif //BACKEND_SITEFUNCTIONALITY_H
