#pragma once

#include <string>
#include "board.h"
using std::string;
namespace minichess_AI
{
    // chessの最長手数は228らしい
    constexpr int MAX_BESTMOVES = 228;

    class minichessAI
    {

    private:
        Square bestMoves_from[MAX_BESTMOVES];
        Square bestMoves_to[MAX_BESTMOVES];
        Piece bestMovesPromotion[MAX_BESTMOVES];
        Board now_analyzed;

    public:
        double tempEvaluator(Board b);
        double alphabeta(Board b, double alpha, double beta, int depth, int depthMax);
    };
}