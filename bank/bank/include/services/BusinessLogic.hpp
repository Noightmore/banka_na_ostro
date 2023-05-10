#ifndef BANK_BUSINESSLOGIC_HPP
#define BANK_BUSINESSLOGIC_HPP

#include "SiteFunctionality.hpp"
#include "include/data/ApplicationDbContext.hpp"

namespace bank::services
{
    class BusinessLogic : public SiteFunctionality
    {
        private:
                data::ApplicationDbContext* database;
                std::string host_ip_address;
                //const std::string default_error_message = "error error";

                void fetchHostIpAddress() override;

                const data::models::UserAccount& getUserAccount_ById(unsigned int id) override;

                const AuthStatus& authorizeUserLogin_ByAccountIdAndPassword(unsigned int id,
                                                                    std::string& password) override;

                const AuthStatus& verifyUserLogin_ByEmail(std::string& email) override;

        public:
                BusinessLogic();
                ~BusinessLogic();

                void startup() override;

                void run() override;





    };
}

#endif //BANK_BUSINESSLOGIC_HPP
