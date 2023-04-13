#ifndef BACKEND_BANKDATA_HPP
#define BACKEND_BANKDATA_HPP


#include <vector>
#include "UserAccount.hpp"

namespace bank::models
{
    class BankData
    {
        private:

            std::vector<UserAccount*> *loggedInUsers;

            explicit BankData(std::vector<UserAccount*> *loggedInUsers);

        public:

            // TODO: add factory method

            ~BankData();
    };
}


#endif //BACKEND_BANKDATA_HPP
