#include <iostream>
#include "bank/include/data/ApplicationDbContext.hpp"

int main()
{
        auto *context = new bank::data::ApplicationDbContext();
        bank::data::models::UserAccount user = context->loadUserFromDatabase_ByAccountId(3);


        return 0;
}
