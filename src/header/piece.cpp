#include "piece.h"

namespace minichess_AI
{
    // definition

    // get RANK(r)
    // if 1 <= r <= 6, return RANK(r), else, return 0
    int ConvRankToWeight(Rank rank)
    {
        RankWeight rw;
        switch (rank)
        {
        case RANK1:
            rw = RANK1W;
            break;
        case RANK2:
            rw = RANK2W;
            break;
        case RANK3:
            rw = RANK3W;
            break;
        case RANK4:
            rw = RANK4W;
            break;
        case RANK5:
            rw = RANK5W;
            break;
        case RANK6:
            rw = RANK6W;
            break;
        default:
            return 0;
        }

        return static_cast<int>(rw);
    }

    // Get Piece variable by a charactor of a FEN string
    Piece ConvFENCharToPiece(char c)
    {
        switch (c)
        {
        case 'K':
            return WKING;
        case 'k':
            return BKING;
        case 'Q':
            return WQUEEN;
        case 'q':
            return BQUEEN;
        case 'B':
            return WBISHOP;
        case 'b':
            return BBISHOP;
        case 'N':
            return WKNIGHT;
        case 'n':
            return BKNIGHT;
        case 'R':
            return WROOK;
        case 'r':
            return BROOK;
        case 'P':
            return WPAWN;
        case 'p':
            return BPAWN;
        }

        return EMPTYSQ;
    }

    // get piece color
    Color GetPieceColor(Piece p)
    {
        return ((p & 0b1000) == 0) ? cBlack : cWhite;
    }
}