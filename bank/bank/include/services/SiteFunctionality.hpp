#ifndef BACKEND_SITEFUNCTIONALITY_H
#define BACKEND_SITEFUNCTIONALITY_H

#include <cstring>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <string>
#include <cstdlib>
#include <memory>
#include <fcgio.h>
#include <fcgiapp.h>
#include <thread>
#include <fstream>

#include "AuthStatus.h"
#include "../data/models/UserAccount.hpp"

namespace bank::services
{
    class SiteFunctionality
    {
        protected:
                virtual void fetchHostIpAddress() = 0;

                virtual const data::models::UserAccount& getUserAccount_ById(unsigned int id) = 0;

                virtual const AuthStatus& authorizeUserLogin_ByAccountIdAndPassword(unsigned int id,
                                                                                    std::string& password) = 0;
                virtual const AuthStatus& verifyUserLogin_ByEmail(std::string& email) = 0;

        public:
                virtual void run() = 0;

                virtual void startup() = 0;
    };
}


#endif //BACKEND_SITEFUNCTIONALITY_H
