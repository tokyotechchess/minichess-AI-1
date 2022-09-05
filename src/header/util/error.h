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

        std::string GetMessage();

        std::string DisplayError();

        // operator

        MCError operator=(const MCError &);
        bool operator==(const MCError &);
        bool operator!=(const MCError &);
    };

    // error types

    namespace mcet
    {
        // Error Generator

        MCError genFENErr(std::string);
        MCError genMoveErr(std::string);
        MCError genMoveWPErr(std::string);
        MCError genTestErr(std::string);

        // if there is no error, status should be 0
        const MCError NoErr;
        const MCError TestErr = genTestErr("");
        const MCError FENErr = genFENErr("");
        const MCError MoveErr = genMoveErr("");
        const MCError MoveWPErr = genMoveWPErr("");

    }
}