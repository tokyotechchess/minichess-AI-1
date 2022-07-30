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
    };

    // error types (constances)

    namespace MCETypes
    {
        const MCError NoErr;
    }
}