#pragma once

#include <string>

/*
error.h

Class "MCError" and its method are defined.
*/
using std::string;
namespace minichess_AI
{
    class MCError
    {
    private:
        int status;
        string message;

    public:
        MCError() : status(0), message(""){};
        MCError(int s, string m) : status(s), message(m){};

        // manipulate variables

        string GetMessage();

        string DisplayError();

        // operator

        MCError operator=(const MCError &);
        bool operator==(const MCError &);
        bool operator!=(const MCError &);
    };

    // error types

    namespace mcet
    {
        // Error Generator

        MCError genFENErr(string);
        MCError genMoveErr(string);
        MCError genMoveWPErr(string);
        MCError genTestErr(string);

        // if there is no error, status should be 0
        const MCError NoErr;
        const MCError TestErr = genTestErr("");
        const MCError FENErr = genFENErr("");
        const MCError MoveErr = genMoveErr("");
        const MCError MoveWPErr = genMoveWPErr("");

    }
}