#include "include/data/ApplicationDbContext.hpp"

namespace bank::data
{

    ApplicationDbContext::ApplicationDbContext()
    {
        bankData = models::BankData::createInstance().release();
    }

    ApplicationDbContext::~ApplicationDbContext()
    {
        delete bankData;
    }

    void ApplicationDbContext::loadUserFromDatabase_ByAccountId(unsigned int id)
    {

    }

    void ApplicationDbContext::addPaymentRecordToAUser_ByAccountId(unsigned int id, models::Payment paymentRecord)
    {

    }
}
