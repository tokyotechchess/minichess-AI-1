#include "error.h"

namespace minichess_AI
{
    // definitions

    std::string MCError::GetMessage()
    {
        return message;
    }

    // get error description as std::string
    // return (error type + error message)
    std::string MCError::DisplayError()
    {
        switch (status)
        {
        case 0:
            return "";
        case 100:
            return "FEN Error : " + message;
        case 200:
            return "Move Error : " + message;
        case 300:
            return "Move Wrong Piece Error : " + message;
        case 10000:
            return "Test Error : " + message;
        default:
            return "Unknown Error : " + message;
        }

        return "";
    }

    // operators

    // assignment operator
    MCError MCError::operator=(const MCError &mce)
    {
        status = mce.status;
        message = mce.message;
        return *this;
    }

    // same status
    bool MCError::operator==(const MCError &mce)
    {
        if (status == mce.status)
            return true;
        else
            return false;
    }

    // not same status
    bool MCError::operator!=(const MCError &mce)
    {
        if (status != mce.status)
            return true;
        else
            return false;
    }
}