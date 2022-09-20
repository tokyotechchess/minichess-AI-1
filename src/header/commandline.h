#pragma once

#include <iostream>
#include <string>
#include "util/error.h"
#include "util/util.h"
#include "piece.h"
#include "board.h"

namespace minichess_AI
{
    struct MCCSetting
    {
        bool displayCastlingPossibility=true;
        bool displaySpendTurn;
        bool displayEnpassantAbleFile=true;
    };
    class CommandLine
    {
    public:
        MCError DisplayBoard(Board *b);
    private:
        MCCSetting setting;
    };
}