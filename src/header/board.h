#pragma once

/*
board.h

Class "Board" and its method are defined.
*/

#include <string>
#include "util/error.h"
#include "util/util.h"
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
        /*
            Variable "turn" is the piece color of the player in this turn.
        */
        Color turn;
        /*
            Variable "enpassantAblePawnFile" is the file of the pawn which can be a enpassant target.
            When there is no such the target, the value is FILEERR.

            example:
            When turn == cWhite, and if black plays c5 to c3 on the pre-turn, enpassantAblePawnFile = CFILE
        */
        File enpassantAblePawnFile;
        /*
            Variable "castlingPossibility" stores possibilities of castling.


            Color who  |
            can castle | Value
            -----------|----------
            No one     | 0
            White      | 1
            Black      | 2
            Both       | 3
        */
        int castlingPossibility;

    public:
        // Constructor

        Board() { InitBoard(); }

        // methods

        MCError InitBoard();
        Color GetTurn();
        File GetEnpassantAblePawnFile();
        bool GetCastlingPossibility(Color);
        int *GetBoard();
        std::string GetBoardFEN();
        Piece GetSquare(Square);
        bool IsChecked(Color);
        MCError SetSquare(Square, Piece);
        MCError SetBoardFEN(std::string fen);
        MCError Move(Square, Square, Piece);
        MCError NullMove();
        MCError LegalMoves(File, Rank, File[17], Rank[17], int *);

        // support methods
        // arguments or return value can be unnatural

        Square IsCheckedByPawn(Square, Color);
        Square IsCheckedByKing(Square, Color);
        Square IsCheckedByHorizontal(Square, Color);
        Square IsCheckedByDiagonal(Square, Color);
        Square IsCheckedByKnight(Square, Color);

        // opeartors

        bool operator==(const Board &b);
        bool operator!=(const Board &b);

    private:
        // private methods (danger methods are here)

        MCError SetBoard(int[5]);
    };
}