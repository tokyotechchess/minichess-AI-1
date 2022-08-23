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
        int GetSquare(File, Rank);
        bool IsChecked(Color);
        MCError SetSquare(File, Rank, Piece);
        MCError SetBoardFEN(std::string fen);
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

        turn = cWhite;
        enpassantAblePawnFile = FILEERR;
        castlingPossibility = 3;

        return mcet::NoErr;
    }

    // get turn
    Color Board::GetTurn() { return turn; }
    // get enpassantAblePawnFile
    File Board::GetEnpassantAblePawnFile() { return enpassantAblePawnFile; }
    // check color's castling possibility
    bool Board::GetCastlingPossibility(Color color)
    {
        return ((color == cWhite) ? ((0b01 & castlingPossibility) != 0) : ((0b10 & castlingPossibility) != 0));
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

    // check that color's king is checked (Color: cWhite, cBlack)
    bool Board::IsChecked(Color color)
    {
        int square[5][6];

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
        Rank krank = RANKERR;
        File kfile = FILEERR;
        Rank okrank = RANKERR;
        File okfile = FILEERR;
        for (File f = AFILE; f <= EFILE; f++)
        {
            for (Rank r = RANK1; r <= RANK6; r++)
            {
                square[f][r] = GetSquare(f, r);
                if (square[f][r] == mk)
                {
                    kfile = f;
                    krank = r;
                }
                if (square[f][r] == ok)
                {
                    okfile = f;
                    okrank = r;
                }
            }
        }

        // color's king is not in the board
        if (kfile == FILEERR)
            return false;

        int i, j, k;

        // king
        if (okfile == FILEERR)
        {
            // Nothing to do now
        }
        else if ((int)okfile - 1 <= (int)kfile && (int)kfile <= (int)okfile + 1 && (int)okrank - 1 <= (int)krank && (int)krank <= (int)okrank + 1)
        {
            return true;
        }

        // knight
        File nfile;
        Rank nrank;
        for (i = 0; i <= 1; i++)
        {
            for (j = 0; j <= 1; j++)
            {
                for (k = 0; k <= 1; k++)
                {
                    nfile = kfile + (1 + i) * (2 * j - 1);
                    nrank = krank + (2 - i) * (2 * k - 1);
                    if (GetSquare(nfile, nrank) == n)
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
                drank = krank + i;
                dfile = kfile + j;
                while (RANK1 <= drank && drank <= RANK6 && AFILE <= dfile && dfile <= EFILE)
                {
                    if (square[dfile][drank] == q || square[dfile][drank] == b)
                    {
                        return true;
                    }
                    else if (square[dfile][drank] != EMPTYSQ)
                    {
                        break;
                    }
                    drank += i;
                    dfile += j;
                }
            }
        }

        // horizontal piece
        int lfile, lrank;
        for (i = -1; i <= 1; i += 2)
        {
            lrank = krank + i;
            lfile = kfile;
            while (RANK1 <= lrank && lrank <= RANK6)
            {
                if (square[lfile][lrank] == q || square[lfile][lrank] == r)
                {
                    return true;
                }
                else if (square[lfile][lrank] != EMPTYSQ)
                {
                    break;
                }
                lrank += i;
            }
        }
        for (i = -1; i <= 1; i += 2)
        {
            lrank = krank;
            lfile = kfile + i;
            while (AFILE <= lfile && lfile <= EFILE)
            {
                if (square[lfile][lrank] == q || square[lfile][lrank] == r)
                {
                    return true;
                }
                else if (square[lfile][lrank] != EMPTYSQ)
                {
                    break;
                }
                lfile += i;
            }
        }

        // pawn
        i = (color == cWhite) ? 1 : -1;
        if (RANK1 <= (int)krank + i && (int)krank + i <= RANK6)
        {
            for (j = -1; j <= 1; j += 2)
            {
                if ((int)kfile + j < AFILE || EFILE < (int)kfile + j)
                {
                    continue;
                }
                if (square[kfile + j][krank + i] == p)
                {
                    return true;
                }
            }
        }

        return false;
    }

    // set a piece of square
    // if piece = EMPTYSQ, delete piece in the square, else, put a piece to the square
    MCError Board::SetSquare(File file, Rank rank, Piece piece)
    {
        files[file] &= 0b111111111111111111111111 - ConvRankToWeight(rank) * 0b1111;
        files[file] += ConvRankToWeight(rank) * (int)piece;

        return mcet::NoErr;
    }

    // set pieces in the whole board by FEN
    MCError Board::SetBoardFEN(std::string FEN)
    {
        File nowf = AFILE;
        Rank nowr = RANK6;
        char c;
        int temp;
        Piece temppiece;
        int phaze = 0;
        bool csetted = false;
        bool finish = false;
        MCError err = mcet::NoErr;

        // set all squares no piece
        for (int i = AFILE; i <= EFILE; i++)
        {
            files[i] = 0;
        }

        // set other variables
        enpassantAblePawnFile = FILEERR;
        castlingPossibility = 0;

        for (int i = 0; i < FEN.length(); i++)
        {
            c = FEN[i];

            if (finish || (err != mcet::NoErr))
            {
                break;
            }

            // to next phaze
            if (c == ' ')
            {
                // finish reading FEN
                if (phaze == 3)
                {
                    break;
                }

                phaze++;
                continue;
            }

            // process at each phaze
            switch (phaze)
            {
            case 0:
                // piece placement

                // empty squares
                if ('0' <= c && c <= '9')
                {
                    temp = (int)nowf + int(c - '0');
                    if (temp > (int)EFILE + 1)
                    {
                        err = mcet::genFENErr(
                            "RANK" + std::to_string((int)nowr + 1) + " has more than 6 files due to too many empty squares");
                        break;
                    }

                    nowf = (temp == (int)EFILE + 1) ? FILEERR : (File)temp;
                    break;
                }

                // pieces
                temppiece = ConvFENCharToPiece(c);
                if (temppiece != EMPTYSQ)
                {
                    if (nowf == FILEERR)
                    {
                        err = mcet::genFENErr(
                            "RANK" + std::to_string((int)nowr + 1) + " has more than 6 files due to too many pieces");
                        break;
                    }

                    SetSquare(nowf, nowr, temppiece);

                    nowf = (nowf == EFILE) ? FILEERR : File((int)nowf + 1);
                    break;
                }

                // new rank
                if (c == '/')
                {
                    // ignore not enough pieces error

                    if (nowr == RANK1)
                    {
                        err = mcet::genFENErr("This FEN has more than 7 ranks");
                        break;
                    }

                    nowf = AFILE;
                    nowr--;
                    break;
                }

                err = mcet::genFENErr("Wrong FEN expression about the piece placement");
                break;

            case 1:
                // turn

                if (!csetted)
                {
                    if (c == 'w' || c == 'W')
                    {
                        turn = cWhite;
                        csetted = true;
                        break;
                    }
                    else if (c == 'b' || c == 'B')
                    {
                        turn = cBlack;
                        csetted = true;
                        break;
                    }
                }

                err = mcet::genFENErr("Wrong FEN expression about the color setting");
                break;

            case 2:
                // castling possibility
                if (c == 'K')
                {
                    if ((castlingPossibility & 0b01) != 0)
                    {
                        err = mcet::genFENErr("Same characters are overused in castling possibility settings");
                        break;
                    }
                    castlingPossibility += 1;
                    break;
                }
                else if (c == 'k')
                {
                    if ((castlingPossibility & 0b10) != 0)
                    {
                        err = mcet::genFENErr("Same characters are overused in castling possibility settings");
                        break;
                    }
                    castlingPossibility += 2;
                    break;
                }
                else if (c == '-')
                {
                    break;
                }

                err = mcet::genFENErr("Wrong FEN expression about the castling possibility");
                break;

            case 3:
                // enpassant target
                if (c == '-')
                {
                    enpassantAblePawnFile = FILEERR;
                    finish = true;
                    break;
                }
                else if ('a' <= c && c <= 'e')
                {
                    enpassantAblePawnFile = (File)(int)(c - 'a');
                    finish = true;
                    break;
                }
                else if ('A' <= c && c <= 'E')
                {
                    enpassantAblePawnFile = (File)(int)(c - 'A');
                    finish = true;
                    break;
                }

                err = mcet::genFENErr("Wrong FEN expression about the en passant");
                break;
            }
        }

        if (err != mcet::NoErr)
            InitBoard();

        return err;
    }

    // move piece
    // ex) Ra2 -> Ra3: Move(AFILE, RANK2, AFILE, RANK3)
    // ex) if castling, when turn == cWhite, Move(AFILE, RANK1, CFILE, RANK1)
    MCError Board::Move(File from_file, Rank from_rank, File to_file, Rank to_rank)
    {
        if (from_file == to_file && from_rank == to_rank)
            return mcet::genMoveErr("To-square is equal to from-square");

        Piece p = (Piece)GetSquare(from_file, from_rank);
        Piece op = (Piece)GetSquare(to_file, to_rank);

        // no piece
        if (p == EMPTYSQ)
            return mcet::genMoveErr("There is no piece in this square");

        // incorrect color, a same color piece exists in to-square
        if (((int)p & 0b1000) == 0)
        {
            if (turn == cBlack)
                return mcet::genMoveErr("This piece is an opponent one");
            if (op != EMPTYSQ && ((int)op && 0b1000) == 0)
                return mcet::genMoveErr("A same color piece exists in to-square");
        }
        else
        {
            if (turn == cWhite)
                return mcet::genMoveErr("This piece is an opponent one");
            if (op != EMPTYSQ && ((int)op && 0b1000) == 1)
                return mcet::genMoveErr("A same color piece exists in to-square");
        }

        // piece type

        bool pawn = false;
        bool knight = false;
        bool king = false;
        bool diagonal = false;
        bool horizontal = false;

        bool loseCastling = false;

        switch (p)
        {
        case WPAWN:
        case BPAWN:
            pawn = true;
            break;
        case WKNIGHT:
        case BKNIGHT:
            knight = true;
            break;
        case WKING:
        case BKING:
            king = true;
            loseCastling = true;
            break;
        case WBISHOP:
        case BBISHOP:
            diagonal = true;
            break;
        case WROOK:
        case BROOK:
            horizontal = true;
            loseCastling = true;
            break;
        case WQUEEN:
        case BQUEEN:
            if (abs((int)from_rank - (int)to_rank) == abs((int)from_file - (int)to_file))
                diagonal = true;
            else
                horizontal = true;
            break;
        default:
            mcet::genMoveErr("Unexpected error when identifing piece type");
            break;
        }

        bool illegal = false;
        bool enpassant = false;
        bool castling = false;
        int temp1, temp2, temp3, temp4;
        Rank tempr1;
        File tempf1, tempf2;
        Piece tempp1;

        if (knight)
        {
            temp1 = abs((int)from_file - (int)to_file);
            temp2 = abs((int)from_rank - (int)to_rank);
            if (temp1 > 2 || temp2 > 2 || temp1 + temp2 != 3)
                illegal = true;
        }

        if (pawn)
        {
            temp1 = (turn == cWhite) ? 1 : -1;
            temp2 = (int)to_rank - (int)from_rank;
            temp3 = (int)to_file - (int)from_file;
            if (temp3 > 1)
                illegal = true;
            if (temp2 == temp1)
            {
                if (temp3 == 1)
                {
                    // take
                    if (op == EMPTYSQ)
                    {
                        // enpassant
                        tempr1 = (turn == cWhite) ? RANK4 : RANK3;
                        tempp1 = (turn == cWhite) ? BPAWN : WPAWN;
                        if (
                            (to_file != enpassantAblePawnFile) ||
                            (to_rank != tempr1) ||
                            (GetSquare(to_file, tempr1 - temp1) != tempp1))
                            illegal = true;
                    }
                }
                else
                {
                    // not take
                    if (op != EMPTYSQ)
                        illegal = true;
                }
            }
            else if (temp2 == 2 * temp2)
            {
                if (op != EMPTYSQ)
                    illegal = true;
                if (temp3 != 0)
                    illegal = true;
                if (turn == cWhite && (from_rank != RANK2 || GetSquare(from_file, RANK3) != EMPTYSQ))
                    illegal = true;
                else if (turn == cBlack && (from_rank != RANK5 || GetSquare(from_file, RANK4) != EMPTYSQ))
                    illegal = true;
            }
            else
            {
                illegal = true;
            }
        }

        if (king)
        {
            if (abs((int)from_rank - (int)to_rank) > 1 || abs((int)from_file - (int)to_file) > 1)
            {
                // castling
                if (turn == cWhite)
                {
                    tempr1 = RANK1;
                    tempf1 = AFILE; // king
                    tempf2 = EFILE; // rook
                    tempp1 = WROOK;
                }
                else
                {
                    tempr1 = RANK6;
                    tempf1 = EFILE; // king
                    tempf2 = AFILE; // rook
                    tempp1 = BROOK;
                }

                if (!GetCastlingPossibility(turn))
                    illegal = true;
                else if (
                    (from_file != tempf1) ||
                    (to_file != CFILE) ||
                    (from_rank != tempr1) ||
                    (to_rank != tempr1))
                    illegal = true;
                else if (
                    (GetSquare(tempf2, tempr1) != tempp1) ||
                    (GetSquare(BFILE, tempr1) != EMPTYSQ) ||
                    (GetSquare(CFILE, tempr1) != EMPTYSQ) ||
                    (GetSquare(DFILE, tempr1) != EMPTYSQ))
                    illegal = true;
                else if (IsChecked(turn) == true)
                    illegal = true;
                else
                {
                    SetSquare(from_file, from_rank, EMPTYSQ);
                    SetSquare(File(((int)from_file + CFILE) / 2), from_rank, p);
                    if (IsChecked(turn) == true)
                    {
                        illegal = true;
                    }
                    else
                    {
                        SetSquare(from_file, from_rank, p);
                        SetSquare(File(((int)from_file + CFILE) / 2), from_rank, EMPTYSQ);
                        castling = true;
                    }
                }
            }
        }

        if (diagonal)
        {
            temp1 = (int)from_file - (int)to_file;
            temp2 = (int)from_rank - (int)to_rank;
            if (abs(temp1) != abs(temp2))
            {
                illegal = true;
            }
            else
            {
                temp3 = temp1 / abs(temp1);
                temp4 = temp2 / abs(temp2);
                for (int i = 1; i < abs(temp1); i++)
                {
                    if (GetSquare(from_file + i * temp3, from_rank + i * temp4) != EMPTYSQ)
                        illegal = true;
                }
            }
        }

        if (horizontal)
        {
            if (from_rank == to_rank)
            {
                temp1 = min((int)from_file, (int)to_file);
                temp2 = max((int)from_file, (int)to_file);
                for (File f = File(temp1 + 1); f < File(temp2); f++)
                {
                    if (GetSquare(f, from_rank) != EMPTYSQ)
                        illegal = true;
                }
            }
            else if (from_file == to_file)
            {
                temp1 = min((int)from_rank, (int)to_rank);
                temp2 = max((int)from_rank, (int)to_rank);
                for (Rank r = Rank(temp1 + 1); r < Rank(temp2); r++)
                {
                    if (GetSquare(from_file, r) != EMPTYSQ)
                        illegal = true;
                }
            }
            else
            {
                illegal = true;
            }
        }

        if (illegal)
            return mcet::genMoveErr("Wrong move played");

        // move

        MCError err;
        Board tempb = *this;

        if (enpassant)
        {
            err = SetSquare(from_file, from_rank, EMPTYSQ);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            err = SetSquare(to_file, to_rank, p);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            err = SetSquare(to_file, (turn == cWhite) ? RANK3 : RANK4, EMPTYSQ);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            enpassantAblePawnFile = to_file;
        }
        else if (castling)
        {
            err = SetSquare(from_file, to_rank, EMPTYSQ);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            err = SetSquare(File(4 - from_file), to_rank, EMPTYSQ);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            err = SetSquare(CFILE, to_rank, p);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            err = SetSquare(File(((int)from_file + CFILE) / 2), to_rank, (turn == cWhite) ? WROOK : BROOK);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
        }
        else
        {
            err = SetSquare(from_file, from_rank, EMPTYSQ);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            err = SetSquare(to_file, to_rank, p);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
        }

    MOVE_ERR_1:
        if (err != mcet::NoErr)
        {
            *this = tempb;
            return err;
        }

        // change variables

        turn++;
        if (loseCastling && GetCastlingPossibility(turn))
            castlingPossibility -= (turn == cWhite) ? 0b01 : 0b10;

        return mcet::NoErr;
    }
}