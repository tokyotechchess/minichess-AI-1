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

// macro to enable base operators
#define ENABLE_BASE_OPERATORS_ON(T)                              \
    ENABLE_INCR_OPERATORS_ON(T)                                  \
    inline T operator+(T d1, int d2) { return T(int(d1) + d2); } \
    inline T operator-(T d1, int d2) { return T(int(d1) - d2); } \
    inline T operator-(T d) { return T(-int(d)); }               \
    inline T &operator+=(T &d1, int d2) { return d1 = d1 + d2; } \
    inline T &operator-=(T &d1, int d2) { return d1 = d1 - d2; }

namespace minichess_AI
{
    // pieces definition
    enum
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

    enum RankWeight
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
    enum Color
    {
        cWhite,
        cBlack,
    };

    // enable increment
    ENABLE_BASE_OPERATORS_ON(Rank);
    ENABLE_BASE_OPERATORS_ON(File);

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
}