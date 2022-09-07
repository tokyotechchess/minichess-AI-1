#pragma once

#include <iostream>

namespace minichess_AI
{
    struct MCCSetting
    {
        bool displayCastlingPossibility;
        bool displaySpendTurn;
    };
    class CommandLine
    {
    private:
        MCCSetting setting;
    };
}