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
                0000: Empty
                if white, * = 0, else, * = 1;
                *001: King
                *010: Pawn
                *011: Queen
                *100: Rook
                *101: Knight
                *110: Bishop
        */
        int column[5];

    public:
        // Constructor

        Board() { InitBoard(); }

        // methods

        MCError InitBoard();
        int *GetBoard();
        int GetSquare(int, int);
        MCError Move(int, int, int, int);
    };

    // definitions

    // initilize board
    MCError Board::InitBoard()
    {
        column[0] = WKING * RANK1 + WPAWN * RANK2 + BPAWN * RANK5 + BROOK * RANK6;
        column[1] = WQUEEN * RANK1 + WPAWN * RANK2 + BPAWN * RANK5 + BKNIGHT * RANK6;
        column[2] = WBISHOP * RANK1 + WPAWN * RANK2 + BPAWN * RANK5 + BBISHOP * RANK6;
        column[3] = WKNIGHT * RANK1 + WPAWN * RANK2 + BPAWN * RANK5 + BQUEEN * RANK6;
        column[4] = WROOK * RANK1 + WPAWN * RANK2 + BPAWN * RANK5 + BKING * RANK6;

        return mcet::NoErr;
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
        if ((rank < 1) || (6 < rank) || (file < 0) || (file > 4))
            return EMPTYSQ;

        int c = this->column[file];
        int r = convRank(rank);
        return (c & (0b1111 * r)) / r;
    }

    // move piece
    // ex) white rook a2 -> a3 : Move(0, WROOK * RANK2, 0, WROOK * RANK3)
    MCError Board::Move(int To_file, int To_piece, int From_file, int From_piece)
    {
        return mcet::NoErr;
    }
}