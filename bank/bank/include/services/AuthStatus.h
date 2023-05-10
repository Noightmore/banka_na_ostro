#ifndef BANK_AUTHSTATUS_H
#define BANK_AUTHSTATUS_H

namespace bank::services
{
    enum class AuthStatus
    {
        AUTHORIZED,
        UNAUTHORIZED,
        ERROR
    };
}

#endif //BANK_AUTHSTATUS_H
