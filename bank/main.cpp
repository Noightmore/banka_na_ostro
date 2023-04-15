#include <iostream>
#include "bank/include/data/ApplicationDbContext.hpp"

int main()
{
        auto *context = new bank::data::ApplicationDbContext();

        context->loadUserFromDatabase_ByAccountId(1);

        return 0;
}
