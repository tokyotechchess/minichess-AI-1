#pragma once

#include <iostream>
#include <string>
#include "../src/header/board.h"
#include "../src/header/util/error.h"

using namespace minichess_AI;

MCError TestGetSquare();
MCError TestSetSquare();
MCError TestSetBoardFEN();
MCError TestIsChecked();
MCError TestMove();
void __Test__Board();