#pragma once

/*
piece.h
Piece definitions.
*/

#include <iostream>

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

    // Square
    // ToDo: 現在はできるだけ早くするために struct にしているが、必要そうだったらクラスにして演算子を付加しても良い。
    struct Square
    {
        File file;
        Rank rank;
    };

    // Color
    // ToDo: piece.h に宣言するのは変かもしれないので, もう少し良いヘッダがあったらそこに移す
    // increment meaning is switching Color; cWhite++ == cBlack, cBlack++ == cWhite
    enum Color : int
    {
        cWhite,
        cBlack,
    };

    // enable increment
    ENABLE_BASE_OPERATORS_ON(Rank);
    ENABLE_BASE_OPERATORS_ON(File);

    // enable calculation between RankWeight and Piece
    inline int operator*(RankWeight rw, Piece p) { return (int(p) * int(rw)); }
    inline int operator*(Piece p, RankWeight rw) { return (rw * p); }

    // change turn
    inline Color operator++(Color &c, int) { return (c = Color(1 - (int)c)); }

    int ConvRankToWeight(Rank);
    Piece ConvFENCharToPiece(char c);

    char ConvPieceToFENChar(Piece p);
    string ConvSquareToPGNString(Square sq);
    inline std::ostream &operator<<(std::ostream &os, const Piece &p)
    {
        os << ConvPieceToFENChar(p);
        return os;
    }
    inline std::ostream &operator<<(std::ostream &os, const Square &sq)
    {
        os << ConvSquareToPGNString(sq);
        return os;
    }

}