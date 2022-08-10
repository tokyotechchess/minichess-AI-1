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
        RANK1 = 0,
        RANK2,
        RANK3,
        RANK4,
        RANK5,
        RANK6,

    };

    enum File : int
    {
        AFILE = 0,
        BFILE,
        CFILE,
        DFILE,
        EFILE,
    };

    // enable increment
    ENABLE_INCR_OPERATORS_ON(Rank);
    ENABLE_INCR_OPERATORS_ON(File);

    // get RANK(r)
    // if 1 <= r <= 6, return RANK(r), else, return 0
    int ConvRankToWeight(int rank)
    {
        switch (rank)
        {
        case RANK1:
            return RANK1W;
            break;
        case RANK2:
            return RANK2W;
            break;
        case RANK3:
            return RANK3W;
            break;
        case RANK4:
            return RANK4W;
            break;
        case RANK5:
            return RANK5W;
            break;
        case RANK6:
            return RANK6W;
            break;
        default:
            return 0;
        }
    }
}