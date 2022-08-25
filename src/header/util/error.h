#pragma once

#include <string>

/*
error.h

Class "MCError" and its method are defined.
*/

namespace minichess_AI
{
    class MCError
    {
    private:
        int status;
        std::string message;

    public:
        MCError() : status(0), message(""){};
        MCError(int s, std::string m) : status(s), message(m){};

        // manipulate variables

        std::string GetMessage()
        {
            return message;
        }

        std::string DisplayError();

        // operator

        // assignment operator
        MCError operator=(const MCError &mce)
        {
            status = mce.status;
            message = mce.message;
            return *this;
        }

        // same status
        bool operator==(const MCError &mce)
        {
            if (status == mce.status)
                return true;
            else
                return false;
        }

        // not same status
        bool operator!=(const MCError &mce)
        {
            if (status != mce.status)
                return true;
            else
                return false;
        }
    };

    // definitions

    // get error description as std::string
    // return (error type + error message)
    std::string MCError::DisplayError()
    {
        switch (status)
        {
        case 100:
            return "FEN Error : " + message;
        case 10000:
            return "Test Error : " + message;
        }

        return "";
    }

    // error types

    namespace mcet
    {
        // Error Generator

        // FEN error
        MCError genFENErr(std::string mes)
        {
            return MCError(100, mes);
        }

        // test error
        MCError genTestErr(std::string mes)
        {
            return MCError(10000, mes);
        }

        // if there is no error, status should be 0
        const MCError NoErr;
        const MCError TestErr = genTestErr("");
        const MCError FENErr = genFENErr("");

    }
}