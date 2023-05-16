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
#include <random>

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


                virtual std::unique_ptr<data::models::Payment> generateRandomPayment_ForAccount(data::models::UserAccount& user) = 0;

                virtual bool attemptToApplyPayment_ForAccount(data::models::UserAccount& account,
                                                              data::models::Payment& payment) = 0;


        public:
                // url is entered in the following format:
                // login=loginId
                // loginId is the id of the user account
                // -1 is returned if no user is logged in
                virtual int getParsedUrl(std::string& query) = 0;

                virtual void run() = 0;

                virtual void startup() = 0;

                virtual AuthStatus verifyUserLogin_ByEmail(unsigned int userId) = 0;
    };
}


#endif //BACKEND_SITEFUNCTIONALITY_H
