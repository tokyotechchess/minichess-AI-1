#pragma once

/*
board.h

Class "Board" and its method are defined.
*/

#include "util/error.h"
#include "piece.h"

namespace minichess_AI
{
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
        int *GetBoard();
        int GetSquare(int, int);
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

    // get board infomation
    int *Board::GetBoard()
    {
        // to avoid returning "column".
        int *c = new int[5];

        for (int i = 0; i < 5; i++)
        {
            c[i] = column[i];
        }

        return c;
    }

    // get square's piece (file: A-file = 0, ..., E-file = 4)
    int Board::GetSquare(int rank, int file)
    {
        int c = this->column[file];
        int r = convRank(rank);
        return ((c / r) - ((c * 0b10000) / r) / 0b10000);
    }
}