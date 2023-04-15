#ifndef BACKEND_APPLICATIONDBCONTEXT_HPP
#define BACKEND_APPLICATIONDBCONTEXT_HPP


#include "include/data/models/BankData.hpp"

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
        models::BankData *bankData;
    };
}


#endif //BACKEND_APPLICATIONDBCONTEXT_HPP
