#pragma once

/*
piece.h
Piece definitions.
*/

// macro to enable increments
#define ENABLE_INCR_OPERATORS_ON(T)                               \
    inline T &operator++(T &d, int) { return d = T(int(d) + 1); } \
    inline T &operator++(T &d) { return d = T(int(d) + 1); }      \
    inline T &operator--(T &d, int) { return d = T(int(d) - 1); } \
    inline T &operator--(T &d) { return d = T(int(d) - 1); }

namespace minichess_AI
{
    // pieces definition
    enum Piece : int
    {
        EMPTYSQ = 0b0000,
        WKING = 0b0001,
        WPAWN,
        WQUEEN,
        WROOK,
        WKNIGHT,
        WBISHOP,
        BKING = 0b1001,
        BPAWN,
        BQUEEN,
        BROOK,
        BKNIGHT,
        BBISHOP,
    };

    enum RankWeight : int
    {
        RANK1W = 0b1,
        RANK2W = 0b10000,
        RANK3W = 0b100000000,
        RANK4W = 0b1000000000000,
        RANK5W = 0b10000000000000000,
        RANK6W = 0b100000000000000000000,
    };

    enum Rank : int
    {
        RANKERR = -1,
        RANK1 = 0,
        RANK2,
        RANK3,
        RANK4,
        RANK5,
        RANK6,

    };

    enum File : int
    {
        FILEERR = -1,
        AFILE = 0,
        BFILE,
        CFILE,
        DFILE,
        EFILE,
    };

    // Color
    // ToDo: piece.h に宣言するのは変かもしれないので, もう少し良いヘッダがあったらそこに移す
    enum Color : int
    {
        cWhite,
        cBlack,
    };

    // enable increment
    ENABLE_INCR_OPERATORS_ON(Rank);
    ENABLE_INCR_OPERATORS_ON(File);

    // enable calculation between RankWeight and Piece
    inline int operator*(RankWeight rw, Piece p) { return (int(p) * int(rw)); }
    inline int operator*(Piece p, RankWeight rw) { return (rw * p); }

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
}