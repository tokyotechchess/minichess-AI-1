#pragma once

#include <iostream>

namespace minichess_AI
{
    class CommandLine
    {
    private:
        struct MCCSetting
        {
            bool displayCastlingPossibility;
            bool displaySpendTurn;
        };
        MCCSetting setting;
    };
}