#include "include/pages/UserAccountPage.hpp"

namespace bank::pages
{
    void UserAccountPage::generatePage(std::string& hostIpAddress, std::string& errorMessage, data::models::UserAccount& userAccount)
    {
        // convert user accout id to string userAccount.getId()
        std::string id = std::to_string(userAccount.getId());

        //std::cout << "Content-type: text/html\r\n\r\n";
        std::cout << "<html>\n";
        std::cout << "<head>\n";
        std::cout << "<title>Bank</title>\n";
        std::cout << "</head>\n";
        std::cout << "<body>\n";
        std::cout << "<h1>Bank</h1>\n";
        this->generateUserData(userAccount);
        //std::cout << "<p>Error Message: " << errorMessage << "</p>\n";
        std::cout << "<form action=\"http://" + hostIpAddress + PAGE_ROUTE + "?login=" + id + "\" method=\"post\">\n";
        std::cout << "<input type=\"submit\" value=\"Submit\">\n";
        std::cout << "</form>\n";
        std::cout << "</body>\n";
        std::cout << "</html>\n";
    }

    void UserAccountPage::generateUserData(data::models::UserAccount &userAccount)
    {
        std::cout << "<h2>User: " << userAccount.getFirstName() << userAccount.getLastName() << "</h2>\n";
        std::cout << "<p>Id: " << userAccount.getId() << "</p>\n";
        std::cout << "<p>Email: " << userAccount.getEmail() << "</p>\n";

        std::cout << "<h3>Balances</h3>\n";
        for (auto balance : userAccount.getBalances())
        {
            std::cout << "<p>Balance: " << balance->getName() << "</p>\n";
            std::cout << "<p>Amount: " << balance->getAmount() << "</p>\n";
            std::cout << "<p>############################################################</p>\n";
        }

        std::cout << "<h3>Payments</h3>\n";
        for (auto payment : userAccount.getPayments())
        {
            std::cout << "<p>Date: " << *payment->getDate() << "</p>\n";
            std::cout << "<p>Payment type " << *payment->getPaymentType() << "</p>\n";
            std::cout << "<p>Sender/Receiver Account: " << *payment->getAccountId() << "</p>\n";
            std::cout << "<p>Amount: " << payment->getBalance()->getAmount() << "</p>\n";
            std::cout << "<p>Currency: " << payment->getBalance()->getName() << "</p>\n";
            std::cout << "<p>############################################################</p>\n";
        }
    }



    void UserAccountPage::generatePage(std::string &hostIpAddress, std::string &errorMessage)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

}
