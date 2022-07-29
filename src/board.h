#pragma once

/*
board.h

Class "Board" and its method are defined.
*/

#include "util/error.h"

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

    class Board
    {
    private:
        /*
            Pieces being in a k-th collumn are stored in column[k].
            (0-indexed: A-file: 0 ... E-file: 4)
            And, 4k-th ~ (4k + 3)-th bit is used for a (k + 1)-rank piece.
            (0-indexed)

            Numbers to identify the type of piece:
                if white, * = 0, else, * = 1;
                *000: King
                *001: Pawn
                *010: Queen
                *011: Rook
                *100: Knight
                *101: Bishop
        */
        int column[5];

    public:
        MCError InitBoard();
    };

    // definitions

    // initilize board
    MCError Board::InitBoard()
    {
        column[0] = WKING * RANK1 + WPAWN * RANK2 + BPAWN * RANK5 + BROOK * RANK6;
        column[1] = WQUEEN * RANK1 + WPAWN * RANK2 + BPAWN * RANK5 + BKNIGHT * RANK6;
        column[2] = WBISHOP * RANK1 + WPAWN * RANK2 + BPAWN * RANK5 + BBISHOP * RANK6;
        column[3] = WKNIGHT * RANK1 + WPAWN * RANK2 + BPAWN * RANK5 + BQUEEN * RANK6;
        column[0] = WROOK * RANK1 + WPAWN * RANK2 + BPAWN * RANK5 + BKING * RANK6;

        return MCError::NoErr;
    }
}