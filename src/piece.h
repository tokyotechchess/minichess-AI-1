#pragma once

/*
piece.h

Piece definitions.
*/

namespace minichess_AI
{
    // pieces definition
    enum
    {
        WKING = 0b0000,
        WPAWN,
        WQUEEN,
        WROOK,
        WKNIGHT,
        WBISHOP,
        BKING = 0b1000,
        BPAWN,
        BQUEEN,
        BROOK,
        BKNIGHT,
        BBISHOP,
    };

    enum
    {
        RANK1 = 0b1,
        RANK2 = 0b10000,
        RANK3 = 0b100000000,
        RANK4 = 0b1000000000000,
        RANK5 = 0b10000000000000000,
        RANK6 = 0b100000000000000000000,
    };

    // get RANK(r)
    // if 1 <= r <= 6, return RANK(r), else, return 0
    int convRank(int rank)
    {
        switch (rank)
        {
        case 1:
            return RANK1;
            break;
        case 2:
            return RANK2;
            break;
        case 3:
            return RANK3;
            break;
        case 4:
            return RANK4;
            break;
        case 5:
            return RANK5;
            break;
        case 6:
            return RANK6;
            break;
        default:
            return 0;
        }
    }
}