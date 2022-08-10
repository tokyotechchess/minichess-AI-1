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
            Pieces being in a k-th collumn are stored in files[k].
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
        int files[5];

    public:
        // Constructor

        Board() { InitBoard(); }

        // methods

        MCError InitBoard();
        int *GetBoard();
        int GetSquare(File, Rank);
        MCError Move(File, Rank, File, Rank);
    };

    // definitions

    // initilize board
    MCError Board::InitBoard()
    {
        files[0] = WKING * RANK1W + WPAWN * RANK2W + BPAWN * RANK5W + BROOK * RANK6W;
        files[1] = WQUEEN * RANK1W + WPAWN * RANK2W + BPAWN * RANK5W + BKNIGHT * RANK6W;
        files[2] = WBISHOP * RANK1W + WPAWN * RANK2W + BPAWN * RANK5W + BBISHOP * RANK6W;
        files[3] = WKNIGHT * RANK1W + WPAWN * RANK2W + BPAWN * RANK5W + BQUEEN * RANK6W;
        files[4] = WROOK * RANK1W + WPAWN * RANK2W + BPAWN * RANK5W + BKING * RANK6W;

        return mcet::NoErr;
    }

    // get board infomation
    int *Board::GetBoard()
    {
        // to avoid returning "files".
        int *f = new int[5];

        for (int i = 0; i < 5; i++)
        {
            f[i] = files[i];
        }

        return f;
    }

    // get square's piece (file: A-file = 0, ..., E-file = 4)
    int Board::GetSquare(File file, Rank rank)
    {
        if ((rank < RANK1) || (RANK6 < rank) || (file < AFILE) || (file > EFILE))
            return EMPTYSQ;

        int c = this->files[file];
        int r = ConvRankToWeight(rank);
        return (c & (0b1111 * r)) / r;
    }

    // move piece
    // ex) white rook a2 -> a3 : Move(WROOK, 0, 2, 0, 3)
    MCError Board::Move(File from_file, Rank from_rank, File to_file, Rank to_rank)
    {
        return mcet::NoErr;
    }
}