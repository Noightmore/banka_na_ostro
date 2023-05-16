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

        const data::models::UserAccount& getUserAccount_ById(unsigned int id) override;

                //const AuthStatus& authorizeUserLogin_ByAccountIdAndPassword(unsigned int id,
                //                                                   std::string& password) override;


        std::unique_ptr<data::models::Payment> generateRandomPayment_ForAccount(data::models::UserAccount& user) override;

                bool attemptToApplyPayment_ForAccount(data::models::UserAccount& account,
                                                      data::models::Payment& payment) override;

        public:
                BusinessLogic();
                ~BusinessLogic();

                int getParsedUrl(std::string& query) override;

                void startup() override;

                void run() override;


        void fetchHostIpAddress() override;

        AuthStatus verifyUserLogin_ByEmail(unsigned int userId) override;
    };
}

#endif //BANK_BUSINESSLOGIC_HPP
