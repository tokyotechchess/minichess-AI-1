#pragma once

/*
board.h

Class "Board" and its method are defined.
*/

#include "util/error.h"
#include "util/util.h"
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
        bool IsChecked(Color);
        MCError Move(int, int, int, int, int);
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

    // check that color's king is checked (Color: cWhite, cBlack)
    bool Board::IsChecked(Color color)
    {
        int square[6][5];

        // searched pieces
        int mk, ok, p, q, r, n, b;
        if (color == cWhite)
        {
            mk = WKING;
            ok = BKING;
            p = BPAWN;
            q = BQUEEN;
            r = BROOK;
            n = BKNIGHT;
            b = BBISHOP;
        }
        else
        {
            mk = BKING;
            ok = WKING;
            p = WPAWN;
            q = WQUEEN;
            r = WROOK;
            n = WKNIGHT;
            b = WBISHOP;
        }

        // search the position of color's king
        int kfile = -1, krank;
        for (int f = 0; f < 5; f++)
        {
            for (int r = 1; r <= 6; r++)
            {
                square[r - 1][f] = GetSquare(r, f);
                if (square[r - 1][f] == mk)
                {
                    kfile = f;
                    krank = r;
                }
            }
        }

        // color's king are not in the board
        if (kfile == -1)
            return false;

        int i, j, k;

        // knight
        int nfile, nrank;
        for (i = 0; i <= 1; i++)
        {
            for (j = 0; j <= 1; j++)
            {
                for (k = 0; k <= 1; k++)
                {
                    nfile = kfile + (1 + i) * (2 * j - 1);
                    nrank = krank + (2 - i) * (2 * k - 1);
                    if (GetSquare(nrank, nfile) == n)
                    {
                        return true;
                    }
                }
            }
        }

        // diagonal pieces
        int dfile, drank;
        for (i = -1; i <= 1; i += 2)
        {
            for (j = -1; j <= 1; j += 2)
            {
                drank = krank;
                dfile = kfile;
                for (k = 0; k < min((1 + i) * (6 - krank) + (1 - i) * (krank - 1), (1 + j) * (4 - kfile) + (1 - j) * kfile) / 2; k++)
                {
                    drank += i;
                    dfile += j;
                    if (square[drank - 1][dfile] == q || square[drank - 1][dfile] == b)
                    {
                        return true;
                    }
                    else if (square[drank - 1][dfile] != EMPTYSQ)
                    {
                        break;
                    }
                }
            }
        }

        // horizontal piece
        int lfile, lrank;
        for (i = -1; i <= 1; i += 2)
        {
            lrank = krank;
            lfile = kfile;
            for (j = 0; j < ((1 + i) * (6 - krank) + (1 - i) * (krank - 1)) / 2; j++)
            {
                lrank += i;
                if (square[lrank - 1][lfile] == q || square[lrank - 1][lfile] == r)
                {
                    return true;
                }
                else if (square[lrank - 1][lfile] != EMPTYSQ)
                {
                    break;
                }
            }
        }
        for (i = -1; i <= 1; i += 2)
        {
            lrank = krank;
            lfile = kfile;
            for (j = 0; j < (1 + i) * (4 - kfile) + (1 - i) * kfile; j++)
            {
                lfile += i;
                if (square[lrank - 1][lfile] == q || square[lrank - 1][lfile] == r)
                {
                    return true;
                }
                else if (square[lrank - 1][lfile] != EMPTYSQ)
                {
                    break;
                }
            }
        }

        // pawn
        i = (color == cWhite) ? 1 : -1;
        for (j = -1; j <= 1; j += 2)
        {
            if (GetSquare(krank + i, kfile + j) == p)
            {
                return true;
            }
        }

        return false;
    }

    // move piece
    // ex) white rook a2 -> a3 : Move(WROOK, 0, 2, 0, 3)
    MCError Board::Move(int piece, int from_file, int from_rank, int to_file, int to_rank)
    {
        return mcet::NoErr;
    }
}