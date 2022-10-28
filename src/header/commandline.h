#pragma once

#include <iostream>
#include <string>
#include "util/error.h"
#include "util/util.h"
#include "piece.h"
#include "board.h"
#include "minichessAI.h"

namespace minichess_AI
{
    struct MCCSetting
    {
        bool displayCastlingPossibility;
        bool displaySpendTurn;
        bool displayEnpassantAbleFile;
    };
    class CommandLine
    {
    public:
        MCError DisplayBoard(Board *b);
        MCError ChangeSetting(MCCSetting set);

    private:
        MCCSetting setting;
    };
}