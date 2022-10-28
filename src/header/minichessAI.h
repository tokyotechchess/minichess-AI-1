#pragma once

#include <string>
#include "board.h"
using std::string;
namespace minichess_AI
{
    // chessの最長手数は228らしい
    constexpr int MAX_BESTMOVES = 228;

    // The max length of array 'legalmoves' recieved by Board::LegalMoves(...)
    constexpr int MAX_LEGALMOVES = 17;
    class minichessAI
    {

    private:
        Square bestMoves_from[MAX_BESTMOVES];
        Square bestMoves_to[MAX_BESTMOVES];
        Piece bestMovesPromotion[MAX_BESTMOVES];

    public:
        double tempEvaluator(Board b);
        MCError tempLegalMoves(Square, Square[MAX_LEGALMOVES], int *);
        double alphabeta(Board b, double alpha, double beta, int depth, int depthMax);
    };
}