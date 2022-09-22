#include "board.h"

namespace minichess_AI
{
    // supporters

    namespace
    {
        Square IsCheckedByPieceType(Board *board, PieceType piecetype, Square kingsq, Color color)
        {
            switch (piecetype)
            {
            case PT_KING:
                return board->IsCheckedByKing(kingsq, color);
            case PT_PAWN:
                return board->IsCheckedByPawn(kingsq, color);
            case PT_KNIGHT:
                return board->IsCheckedByKnight(kingsq, color);
            case PT_HORIZONTAL:
                return board->IsCheckedByHorizontal(kingsq, color);
            case PT_DIAGONAL:
                return board->IsCheckedByDiagonal(kingsq, color);
            }

            return SQUAREERR;
        }

        MCError LMP0C_NotTake(Board *board, Square square, Square legalmoves[MAX_LEGALMOVES], int *count, int temp1)
        {
            Rank tempr1;
            if (board->GetSquare(Square{square.file, square.rank + 1 * temp1}) == EMPTYSQ)
            {
                legalmoves[*count] = Square{square.file, square.rank + 1 * temp1};
                *count++;
                tempr1 = (board->GetTurn() == cWhite) ? RANK2 : RANK5;
                if (square.rank == tempr1 && board->GetSquare(Square{square.file, square.rank + 2 * temp1}) == EMPTYSQ)
                {
                    legalmoves[*count] = Square{square.file, square.rank + 2 * temp1};
                    *count++;
                }
            }
        }

        MCError LMP0C_Take(Board *board, Square square, Square legalmoves[MAX_LEGALMOVES], int *no_moves, int temp1, Color turn)
        {
            File tempf1;
            Color enturn = turn;
            enturn++;
            if (square.file != AFILE)
            {
                if (GetPieceColor(board->GetSquare(Square{square.file - 1, square.rank + temp1})) == enturn)
                {
                    legalmoves[*no_moves] = Square{square.file - 1, square.rank + temp1};
                    *no_moves++;
                }
            }
            if (square.file != EFILE)
            {
                if (GetPieceColor(board->GetSquare(Square{square.file + 1, square.rank + temp1})) == enturn)
                {
                    legalmoves[*no_moves] = Square{square.file + 1, square.rank + temp1};
                    *no_moves++;
                }
            }
            if (square.rank = (turn == cWhite) ? RANK3 : RANK4)
            {
                if ((tempf1 = board->GetEnpassantAblePawnFile()) != FILEERR)
                {
                    if (abs((int)(tempf1 - square.file)) == 1)
                    {
                        if (
                            (board->GetSquare(Square{tempf1, square.rank}) == ((turn == cWhite) ? BBISHOP : WBISHOP)) &&
                            (board->GetSquare(Square{tempf1, square.rank + temp1}) == EMPTYSQ))
                        {
                            legalmoves[*no_moves] = Square{tempf1, square.rank + temp1};
                            *no_moves++;
                        }
                    }
                }
            }
        }

        MCError LegalMovesPawn0Checked(Board *board, Square square, Square kingsq, Square legalmoves[MAX_LEGALMOVES], int *no_moves)
        {
            int i, rdir, fdir, temp1;
            bool able;
            Rank tempr1;
            File tempf1;
            Piece roo, bis, que, tempp1;
            Color turn = board->GetTurn();

            if ((turn == cWhite) ? (square.rank == RANK6) : (square.rank == RANK1))
            {
                *no_moves = 0;
                return mcet::NoErr;
            }

            temp1 = (turn == cWhite) ? 1 : -1;

            if (kingsq.file == square.file)
            {
                // same file as king's one

                // not take

                LMP0C_NotTake(board, square, legalmoves, no_moves, temp1);

                // take

                able = true;
                rdir = (kingsq.rank < square.rank) ? 1 : -1;
                if (turn == cWhite)
                {
                    roo = BBISHOP;
                    que = BQUEEN;
                }
                else
                {
                    roo = WBISHOP;
                    que = WQUEEN;
                }
                for (Rank r = square.rank + rdir;; r += rdir)
                {
                    tempp1 = board->GetSquare(Square{square.file, r});
                    if (tempp1 == roo || tempp1 == que)
                    {
                        able = false;
                        break;
                    }
                    else if (tempp1 != EMPTYSQ)
                    {
                        break;
                    }
                    if (r == RANK1 && r == RANK6)
                    {
                        break;
                    }
                }

                if (able)
                {
                    LMP0C_Take(board, square, legalmoves, no_moves, temp1, turn);
                }
            }
            else if (kingsq.rank == square.rank)
            {
                // same rank as king's

                // find whether pinned

                able = true;

                if (square.file != AFILE && square.file != EFILE)
                {
                    fdir = (kingsq.file < square.file) ? 1 : -1;
                    if (turn == cWhite)
                    {
                        roo = BBISHOP;
                        que = BQUEEN;
                    }
                    else
                    {
                        roo = WBISHOP;
                        que = WQUEEN;
                    }

                    for (File f = square.file + fdir;; f += fdir)
                    {
                        tempp1 = board->GetSquare(Square{f, square.rank});
                        if (tempp1 == roo || tempp1 == que)
                        {
                            able = false;
                        }
                        else if (tempp1 != EMPTYSQ)
                        {
                            break;
                        }
                        if (f == AFILE || f == EFILE)
                        {
                            break;
                        }
                    }
                }

                if (able)
                {
                    // not take

                    LMP0C_NotTake(board, square, legalmoves, no_moves, temp1);

                    // take

                    LMP0C_Take(board, square, legalmoves, no_moves, temp1, turn);
                }
            }
            else if (abs((int)square.file - (int)kingsq.file) == abs((int)square.rank - (int)kingsq.rank))
            {
                fdir = (kingsq.file < square.file) ? 1 : -1;
                rdir = (kingsq.rank < square.rank) ? 1 : -1;

                i = 0;

                tempf1 = square.file;
                tempr1 = square.rank;
                able = true;
                if (turn == cWhite)
                {
                    bis = BBISHOP;
                    que = BQUEEN;
                }
                else
                {
                    bis = WBISHOP;
                    que = WQUEEN;
                }

                while (tempf1 != AFILE && tempf1 != EFILE && tempr1 != RANK1 && tempr1 != RANK6)
                {
                    i++;
                    tempf1 += fdir;
                    tempr1 += rdir;
                    tempp1 = board->GetSquare(Square{tempf1, tempr1});
                    if (tempp1 == bis || tempp1 == que)
                    {
                        able = false;
                        break;
                    }
                    else if (tempp1 == EMPTYSQ)
                    {
                        break;
                    }
                }

                if (able)
                {
                    // not take

                    LMP0C_NotTake(board, square, legalmoves, no_moves, temp1);

                    // take

                    LMP0C_Take(board, square, legalmoves, no_moves, temp1, turn);
                }
                else if (i == 1)
                {
                    legalmoves[*no_moves] = Square{tempf1, tempr1};
                    *no_moves++;
                }
            }
            else
            {
                // not take

                LMP0C_NotTake(board, square, legalmoves, no_moves, temp1);

                // take

                LMP0C_Take(board, square, legalmoves, no_moves, temp1, turn);
            }

            return mcet::NoErr;
        }

        MCError LegalMovesPawn1Checked(Board *board, Square square, Square kingsq, Square legalmoves[MAX_LEGALMOVES],
                                       int *no_moves, Square movableSquares[5], int no_movableSquares, PieceType checkingPieceType)
        {
            Color turn = board->GetTurn();
            Color enturn = turn;
            enturn++;
            int temp1 = (turn == cWhite) ? 1 : -1;
            File mvfile;
            Rank mvrank;
            Piece tempp1, tempp2, pawn = (turn == cWhite) ? WPAWN : BPAWN;

            for (int i = 0; i < no_movableSquares; i++)
            {
                mvfile = movableSquares[i].file;
                mvrank = movableSquares[i].rank;
                tempp1 = board->GetSquare(Square{mvfile, mvrank});

                if (mvrank - square.rank == temp1)
                {
                    switch (abs((int)(mvfile - square.file)))
                    {
                    case 0:
                        if (tempp1 == EMPTYSQ)
                        {
                            board->SetSquare(square, EMPTYSQ);
                            board->SetSquare(movableSquares[i], pawn);

                            if (IsCheckedByPieceType(board, checkingPieceType, kingsq, turn) == SQUAREERR)
                            {
                                legalmoves[*no_moves] = movableSquares[i];
                                *no_moves++;
                            }

                            board->SetSquare(square, pawn);
                            board->SetSquare(movableSquares[i], EMPTYSQ);
                        }
                        break;
                    case 1:
                        if (board->GetEnpassantAblePawnFile() == mvfile &&
                            mvrank == ((turn == cWhite) ? RANK4 : RANK3) &&
                            tempp1 == EMPTYSQ)
                        {
                            tempp2 = board->GetSquare(Square{mvfile, mvrank - temp1});
                            if (GetPieceColor(tempp2) == enturn)
                            {
                                board->SetSquare(Square{mvfile, mvrank - temp1}, EMPTYSQ);
                                board->SetSquare(movableSquares[i], pawn);
                                board->SetSquare(square, EMPTYSQ);

                                if (IsCheckedByPieceType(board, checkingPieceType, kingsq, turn) == SQUAREERR)
                                {
                                    legalmoves[*no_moves] = movableSquares[i];
                                    *no_moves++;
                                }

                                board->SetSquare(Square{mvfile, mvrank - temp1}, tempp2);
                                board->SetSquare(movableSquares[i], EMPTYSQ);
                                board->SetSquare(square, pawn);
                            }
                        }
                        else if (GetPieceColor(tempp1) == enturn)
                        {
                            tempp2 = board->GetSquare(movableSquares[i]);
                            board->SetSquare(movableSquares[i], pawn);
                            board->SetSquare(square, EMPTYSQ);

                            if (IsCheckedByPieceType(board, checkingPieceType, kingsq, turn) == SQUAREERR)
                            {
                                legalmoves[*no_moves] = movableSquares[i];
                                *no_moves++;
                            }

                            board->SetSquare(movableSquares[i], EMPTYSQ);
                            board->SetSquare(square, pawn);
                        }
                    }
                }
                else if (mvrank - square.rank == temp1 * 2)
                {
                    if (mvrank == ((turn == cWhite) ? RANK4 : RANK3) && mvfile == square.file)
                    {
                        if (
                            tempp1 == EMPTYSQ &&
                            board->GetSquare(Square{mvfile, (turn == cWhite) ? RANK3 : RANK4}) == EMPTYSQ)
                        {
                            board->SetSquare(movableSquares[i], pawn);
                            board->SetSquare(square, EMPTYSQ);

                            if (IsCheckedByPieceType(board, checkingPieceType, kingsq, turn) == SQUAREERR)
                            {
                                legalmoves[*no_moves] = movableSquares[i];
                                *no_moves++;
                            }

                            board->SetSquare(movableSquares[i], EMPTYSQ);
                            board->SetSquare(square, pawn);
                        }
                    }
                }
            }

            return mcet::NoErr;
        }

        MCError LegalMovesKing(Board *board, Square square, Square legalmoves[MAX_LEGALMOVES], int *no_moves)
        {
            bool isAttacked[5][6];
            int i, j, k, m, n, l, r, b, f, temp1, temp2;
            Piece p;
            Color turn = board->GetTurn();
            Color enturn = turn;
            enturn++;

            // search attacked squares
            for (i = 0; i < 5; i++)
            {
                for (j = 0; j < 6; j++)
                {
                    if (GetPieceColor(p) == enturn)
                    {
                        switch (p)
                        {
                        case WKING:
                        case BKING:
                            l = -1;
                            r = 1;
                            b = -1;
                            f = 1;

                            if (i == AFILE)
                                l = 1;
                            else if (i == EFILE)
                                r = -1;
                            if (j == RANK1)
                                b = 1;
                            else if (j == RANK6)
                                f = -1;

                            for (k = b; k <= f; k += 2)
                            {
                                for (m = (l == -1) ? -1 : 0; m <= (r == 1) ? 1 : 0; m++)
                                {
                                    isAttacked[i + m][j + k] = true;
                                }
                            }
                            for (k = l; k <= r; k += 2)
                            {
                                isAttacked[i + k][j] = true;
                            }
                            break;
                        case WPAWN:
                        case BPAWN:
                            if (j != ((enturn == cWhite) ? RANK6 : RANK1))
                            {
                                temp1 = (enturn == cWhite) ? 1 : -1;
                                if (i != AFILE)
                                {
                                    isAttacked[i - 1][j] = true;
                                }
                                if (i != EFILE)
                                {
                                    isAttacked[i + 1][j] = true;
                                }
                            }
                            break;
                        case WKNIGHT:
                        case BKNIGHT:
                            for (k = 0; k <= 1; k++)
                            {
                                for (m = 0; m <= 1; m++)
                                {
                                    for (n = 0; n <= 1; n++)
                                    {
                                        temp1 = i + (1 + k) * (2 * m - 1);
                                        temp2 = j + (2 - k) * (2 * n + 1);
                                        if (
                                            AFILE <= temp1 && temp1 <= EFILE && RANK1 <= temp2 && temp2 <= RANK6)
                                        {
                                            isAttacked[temp1][temp2] = true;
                                        }
                                    }
                                }
                            }
                            break;
                        case WBISHOP:
                        case BBISHOP:
                            for (k = -1; k <= 1; k += 2)
                            {
                                for (m = -1; m <= 1; m += 2)
                                {
                                    for (n = 1;; n++)
                                    {
                                        temp1 = i + k * n;
                                        temp2 = j + m * n;
                                        if (temp1 < AFILE || EFILE < temp1 || temp2 < RANK1 || RANK6 < temp2)
                                            break;
                                        if (board->GetSquare(Square{(File)temp1, (Rank)temp2}) != EMPTYSQ)
                                            break;
                                        isAttacked[temp1][temp2] = true;
                                    }
                                }
                            }
                            break;
                        case WROOK:
                        case BROOK:
                            for (k = 0; k <= 1; k++)
                            {
                                for (m = -1; m <= 1; m += 2)
                                {
                                    for (n = m;; n += m)
                                    {
                                        temp1 = i + k * n;
                                        temp2 = j + (1 - k) * n;
                                        if (temp1 < AFILE || EFILE < temp1 || temp2 < RANK1 || RANK6 < temp2)
                                            break;
                                        if (board->GetSquare(Square{(File)temp1, (Rank)temp2}) != EMPTYSQ)
                                            break;
                                        isAttacked[temp1][temp2] = true;
                                    }
                                }
                            }
                            break;
                        case WQUEEN:
                        case BQUEEN:
                            for (k = -1; k <= 1; k += 2)
                            {
                                for (m = -1; m <= 1; m += 2)
                                {
                                    for (n = 1;; n++)
                                    {
                                        temp1 = i + k * n;
                                        temp2 = j + m * n;
                                        if (temp1 < AFILE || EFILE < temp1 || temp2 < RANK1 || RANK6 < temp2)
                                            break;
                                        if (board->GetSquare(Square{(File)temp1, (Rank)temp2}) != EMPTYSQ)
                                            break;
                                        isAttacked[temp1][temp2] = true;
                                    }
                                }
                            }
                            for (k = 0; k <= 1; k++)
                            {
                                for (m = -1; m <= 1; m += 2)
                                {
                                    for (n = m;; n += m)
                                    {
                                        temp1 = i + k * n;
                                        temp2 = j + (1 - k) * n;
                                        if (temp1 < AFILE || EFILE < temp1 || temp2 < RANK1 || RANK6 < temp2)
                                            break;
                                        if (board->GetSquare(Square{(File)temp1, (Rank)temp2}) != EMPTYSQ)
                                            break;
                                        isAttacked[temp1][temp2] = true;
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
            }

            // search legal moves

            l = -1;
            r = 1;
            b = -1;
            f = 1;

            if (square.file == AFILE)
                l = 1;
            else if (square.file == EFILE)
                r = -1;
            if (square.rank = RANK1)
                b = 1;
            else if (square.rank == RANK6)
                f = -1;

            for (k = b; k <= f; k += 2)
            {
                for (m = (l == -1) ? -1 : 0; m <= (r == 1) ? 1 : 0; m++)
                {
                    if (!isAttacked[square.file + m][square.rank + k])
                    {
                        legalmoves[*no_moves] = Square{File(square.file + m), Rank(square.rank + k)};
                        *no_moves++;
                    }
                }
            }
            for (k = l; k <= r; k += 2)
            {
                if (!isAttacked[square.file + k][square.rank])
                {
                    legalmoves[*no_moves] = Square{File(square.file + k), Rank(square.rank)};
                    *no_moves++;
                }
            }

            if (board->GetCastlingPossibility(turn))
            {
                if (turn == cWhite && square == Square{AFILE, RANK1})
                {
                    if (board->GetSquare(Square{EFILE, RANK1}) == WROOK)
                    {
                        if (!(isAttacked[AFILE][RANK1] || isAttacked[BFILE][RANK1] || isAttacked[CFILE][RANK1]))
                        {
                            legalmoves[*no_moves] = Square{CFILE, RANK1};
                        }
                    }
                }
                else if (turn == cBlack && square == Square{EFILE, RANK6})
                {
                    if (board->GetSquare(Square{AFILE, RANK6}) == WROOK)
                    {
                        if (!(isAttacked[EFILE][RANK6] || isAttacked[DFILE][RANK6] || isAttacked[CFILE][RANK6]))
                        {
                            legalmoves[*no_moves] = Square{CFILE, RANK6};
                        }
                    }
                }
            }

            return mcet::NoErr;
        }

        MCError LegalMovesKnight0Checked(Board *board, Square square, Square kingsq, Square legalmoves[MAX_LEGALMOVES], int *no_moves)
        {
            bool able = true, check = true;
            int fdir, rdir, i, j, k, temp1, temp2;
            File tempf1;
            Rank tempr1;
            Color turn = board->GetTurn();
            Piece checkableP1, checkableP2, tempp1;

            checkableP1 = (turn == cWhite) ? BQUEEN : WQUEEN;

            if (square.file == kingsq.file)
            {
                fdir = 0;
                rdir = (square.rank > kingsq.rank) ? 1 : -1;
                checkableP2 = (turn == cWhite) ? BROOK : WROOK;
            }
            else if (square.rank == kingsq.rank)
            {
                fdir = (square.file > kingsq.file) ? 1 : -1;
                rdir = 0;
                checkableP2 = (turn == cWhite) ? BROOK : WROOK;
            }
            else if (abs((int)square.file - (int)kingsq.file) == abs((int)square.rank - (int)kingsq.rank))
            {
                fdir = (square.file > kingsq.file) ? 1 : -1;
                rdir = (square.rank > kingsq.rank) ? 1 : -1;
                checkableP2 = (turn == cWhite) ? BBISHOP : WBISHOP;
            }
            else
            {
                check = false;
            }

            if (check)
            {
                tempf1 = square.file;
                tempr1 = square.rank;
                while (AFILE < tempf1 && tempf1 < EFILE && RANK1 < tempr1 && tempr1 < RANK6)
                {
                    tempf1 += fdir;
                    tempr1 += rdir;
                    tempp1 = board->GetSquare(Square{tempf1, tempr1});
                    if (tempp1 == checkableP1 || tempp1 == checkableP2)
                    {
                        able = false;
                    }
                    else if (tempp1 == EMPTYSQ)
                    {
                        break;
                    }
                }
            }

            if (able)
            {
                for (i = 0; i <= 1; i++)
                {
                    for (j = 0; j <= 1; j++)
                    {
                        for (k = 0; k <= 1; k++)
                        {
                            temp1 = (int)square.file + (i + 1) * (2 * j - 1);
                            temp2 = (int)square.file + (2 - i) * (2 * k - 1);

                            if (AFILE <= temp1 && temp1 <= EFILE && RANK1 <= temp2 && temp2 <= RANK6)
                            {
                                legalmoves[*no_moves] = Square{(File)temp1, (Rank)temp2};
                                *no_moves++;
                            }
                        }
                    }
                }
            }

            return mcet::NoErr;
        }

        MCError LegalMovesKnight1Checked(Board *board, Square square, Square kingsq, Square legalmoves[MAX_LEGALMOVES],
                                         int *no_moves, Square movableSquares[5], int no_movableSquares, PieceType checkingPieceType)
        {
            int i, temp1, temp2;
            Color turn = board->GetTurn();
            Piece knight = (turn == cWhite) ? WKNIGHT : BKNIGHT, tempp1;

            for (i = 0; i < no_movableSquares; i++)
            {
                temp1 = (int)square.file - (int)movableSquares[i].file;
                temp2 = (int)square.rank - (int)movableSquares[i].rank;
                if (abs(temp1) + abs(temp2) == 3 && abs(temp1) != 0 && abs(temp2) != 0)
                {
                    tempp1 = board->GetSquare(movableSquares[i]);
                    board->SetSquare(movableSquares[i], knight);
                    board->SetSquare(square, EMPTYSQ);

                    if (IsCheckedByPieceType(board, checkingPieceType, kingsq, turn) == SQUAREERR)
                    {
                        legalmoves[*no_moves] = movableSquares[i];
                        *no_moves;
                    }

                    board->SetSquare(movableSquares[i], tempp1);
                    board->SetSquare(square, knight);
                }
            }

            return mcet::NoErr;
        }
    }

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

    std::string Board::GetBoardFEN()
    {
        std::string FEN;
        Piece piece_num;
        int count = 0;
        for (Rank r = RANK6; r >= RANK1; r--)
        {
            for (File f = AFILE; f <= EFILE; f++)
            {
                piece_num = GetSquare(Square{f, r});
                if (piece_num == 0)
                {
                    count++;
                }
                else
                {
                    if (count != 0)
                    {
                        FEN += std::to_string(count);
                        count = 0;
                    }
                    FEN += ConvPieceToFENChar(piece_num);
                }
            }
            if (count != 0)
            {
                FEN += std::to_string(count);
            }
            FEN += "/";
            count = 0;
        }
        FEN.pop_back();
        //ここまでコマの位置
        FEN += " ";
        if (turn == cWhite)
        {
            FEN += "w ";
        }
        else
        {
            FEN += "b ";
        }
        //ここまで手番
        if (GetCastlingPossibility(cWhite))
        {
            FEN += "K";
        }
        if (GetCastlingPossibility(cBlack))
        {
            FEN += "k";
        }
        //ここまでキャスリングの可否
        if (enpassantAblePawnFile == FILEERR)
        {
            FEN += " -";
        }
        else
        {
            FEN += " ";
            FEN += char(enpassantAblePawnFile + 'a');        // ascii変換 0 + 97 -> a
            FEN += std::to_string((turn == cWhite) ? 4 : 3); // white pawn : 3, black pawn : 4
        }
        //ここまでアンパッサン
        return FEN;
    }

    // get square's piece (file: A-file = 0, ..., E-file = 4)
    Piece Board::GetSquare(Square square)
    {
        File file = square.file;
        Rank rank = square.rank;
        if ((rank < RANK1) || (RANK6 < rank) || (file < AFILE) || (file > EFILE))
            return EMPTYSQ;

        int c = this->files[file];
        int r = ConvRankToWeight(rank);
        return Piece((c & (0b1111 * r)) / r);
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
                square[f][r] = GetSquare(Square{f, r});
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
                    if (GetSquare(Square{nfile, nrank}) == n)
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
    MCError Board::SetSquare(Square square, Piece piece)
    {
        files[square.file] &= 0b111111111111111111111111 - ConvRankToWeight(square.rank) * 0b1111;
        files[square.file] += ConvRankToWeight(square.rank) * (int)piece;

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

                    SetSquare(Square{nowf, nowr}, temppiece);

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

    // !danger
    // set pieces in the whole squares
    // put arrays to initialize files
    MCError Board::SetBoard(int new_files[5])
    {
        for (int i = 0; i < 5; i++)
        {
            files[i] = new_files[i];
        }

        return mcet::NoErr;
    }

    // move piece
    // ex) Ra2 -> Ra3: Move(AFILE, RANK2, AFILE, RANK3, EMPTYSQ)
    // ex) if castling, when turn == cWhite, Move(AFILE, RANK1, CFILE, RANK1, EMPTYSQ)
    // promote_piece is used only when pawn is promoted (so if not promote, any pieces is OK)
    // ex) Ra2 -> Ra3: Move(AFILE, RANK2, AFILE, RANK3, BKING)
    // ex) a5 -> a6: Move(AFILE, RANK5, AFILE, RANK6, WQUEEN)
    MCError Board::Move(Square from_square, Square to_square, Piece promote_piece)
    {
        File from_file = from_square.file, to_file = to_square.file;
        Rank from_rank = from_square.rank, to_rank = to_square.rank;

        if (from_file == to_file && from_rank == to_rank)
            return mcet::genMoveErr("To-square is equal to from-square");

        Piece p = (Piece)GetSquare(Square{from_file, from_rank});
        Piece op = (Piece)GetSquare(Square{to_file, to_rank});

        // no piece
        if (p == EMPTYSQ)
            return mcet::genMoveWPErr("There is no piece in this square");

        // incorrect color, a same color piece exists in to-square
        if (((int)p & 0b1000) == 0)
        {
            if (turn == cBlack)
                return mcet::genMoveWPErr("This piece is an opponent one");
            if (op != EMPTYSQ && ((int)op & 0b1000) == 0)
                return mcet::genMoveErr("A same color piece exists in to-square");
        }
        else
        {
            if (turn == cWhite)
                return mcet::genMoveWPErr("This piece is an opponent one");
            if (op != EMPTYSQ && ((int)op & 0b1000) == 0b1000)
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
            mcet::genMoveWPErr("Unexpected error when identifing piece type");
            break;
        }

        bool illegal = false;
        bool enpassant = false;
        bool pawn2sq = false;
        bool castling = false;
        bool promotion = false;
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
            // promotion

            if (turn == cWhite && to_rank == RANK6)
            {
                switch (promote_piece)
                {
                case WQUEEN:
                case WBISHOP:
                case WKNIGHT:
                case WROOK:
                    promotion = true;
                    break;
                default:
                    return mcet::genMoveErr("Promotion error : Pawn can't be promoted to such a piece");
                }
            }
            else if (turn == cBlack && to_rank == RANK1)
            {
                switch (promote_piece)
                {
                case BQUEEN:
                case BBISHOP:
                case BKNIGHT:
                case BROOK:
                    promotion = true;
                    break;
                default:
                    return mcet::genMoveErr("Promotion error : Pawn can't be promoted to such a piece");
                }
            }

            // movement

            temp1 = (turn == cWhite) ? 1 : -1;
            temp2 = (int)to_rank - (int)from_rank;
            temp3 = abs((int)to_file - (int)from_file);
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
                            (GetSquare(Square{to_file, tempr1 - temp1}) != tempp1))
                            illegal = true;
                        else
                            enpassant = true;
                    }
                }
                else
                {
                    // not take
                    if (op != EMPTYSQ)
                        illegal = true;
                }
            }
            else if (temp2 == 2 * temp1)
            {
                if (op != EMPTYSQ)
                    illegal = true;
                else if (temp3 != 0)
                    illegal = true;
                else if (turn == cWhite && (from_rank != RANK2 || GetSquare(Square{from_file, RANK3}) != EMPTYSQ))
                    illegal = true;
                else if (turn == cBlack && (from_rank != RANK5 || GetSquare(Square{from_file, RANK4}) != EMPTYSQ))
                    illegal = true;
                else
                    pawn2sq = true;
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
                    (GetSquare(Square{tempf2, tempr1}) != tempp1) ||
                    (GetSquare(Square{BFILE, tempr1}) != EMPTYSQ) ||
                    (GetSquare(Square{CFILE, tempr1}) != EMPTYSQ) ||
                    (GetSquare(Square{DFILE, tempr1}) != EMPTYSQ))
                    illegal = true;
                else if (IsChecked(turn) == true)
                    illegal = true;
                else
                {
                    SetSquare(Square{from_file, from_rank}, EMPTYSQ);
                    SetSquare(Square{File(((int)from_file + CFILE) / 2), from_rank}, p);
                    if (IsChecked(turn) == true)
                    {
                        illegal = true;
                    }
                    else
                    {
                        castling = true;
                    }
                    SetSquare(Square{from_file, from_rank}, p);
                    SetSquare(Square{File(((int)from_file + CFILE) / 2), from_rank}, EMPTYSQ);
                }
            }
        }

        if (diagonal)
        {
            temp1 = (int)to_file - (int)from_file;
            temp2 = (int)to_rank - (int)from_rank;
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
                    if (GetSquare(Square{from_file + i * temp3, from_rank + i * temp4}) != EMPTYSQ)
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
                    if (GetSquare(Square{f, from_rank}) != EMPTYSQ)
                        illegal = true;
                }
            }
            else if (from_file == to_file)
            {
                temp1 = min((int)from_rank, (int)to_rank);
                temp2 = max((int)from_rank, (int)to_rank);
                for (Rank r = Rank(temp1 + 1); r < Rank(temp2); r++)
                {
                    if (GetSquare(Square{from_file, r}) != EMPTYSQ)
                        illegal = true;
                }
            }
            else
            {
                illegal = true;
            }
        }

        if (illegal)
            return mcet::genMoveErr("illegal move : this type of piece can't move like this");

        // initialize enpassantAblePawnFile

        enpassantAblePawnFile = FILEERR;

        // move

        MCError err;
        int *temp_files;
        temp_files = new int[5];
        temp_files = GetBoard();

        if (enpassant)
        {
            err = SetSquare(Square{from_file, from_rank}, EMPTYSQ);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            err = SetSquare(Square{to_file, to_rank}, p);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            err = SetSquare(Square{to_file, (turn == cWhite) ? RANK3 : RANK4}, EMPTYSQ);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
        }
        else if (castling)
        {
            err = SetSquare(Square{from_file, to_rank}, EMPTYSQ);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            err = SetSquare(Square{File(4 - from_file), to_rank}, EMPTYSQ);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            err = SetSquare(Square{CFILE, to_rank}, p);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            err = SetSquare(Square{File(((int)from_file + CFILE) / 2), to_rank}, (turn == cWhite) ? WROOK : BROOK);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
        }
        else
        {
            err = SetSquare(Square{from_file, from_rank}, EMPTYSQ);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
            err = SetSquare(Square{to_file, to_rank}, p);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
        }

        // promotion

        if (promotion)
        {
            err = SetSquare(Square{to_file, to_rank}, promote_piece);
            if (err != mcet::NoErr)
                goto MOVE_ERR_1;
        }

        // check

        if (IsChecked(turn))
            err = mcet::genMoveErr("illegal move : if this move played, turn's player will be checkmated");

    MOVE_ERR_1:
        if (err != mcet::NoErr)
        {
            SetBoard(temp_files);
            return err;
        }

        // change variables

        if (loseCastling && GetCastlingPossibility(turn))
            castlingPossibility -= (turn == cWhite) ? 0b01 : 0b10;
        turn++;

        if (pawn2sq)
            enpassantAblePawnFile = from_file;

        delete temp_files;

        return mcet::NoErr;
    }

    // null move
    // skip this turn; turn moves to another color and enpassantAblePawnFile = FILEERR
    MCError Board::NullMove()
    {
        turn++;
        enpassantAblePawnFile = FILEERR;

        return mcet::NoErr;
    }

    // search all legal moves
    // recieve the squares where the piece in the specified square can move.
    // the 5-th argument is the number of legal moves.
    // the length of legalmoves is 'MAX_LEGALMOVES'.
    // promotions are not counted.
    MCError Board::LegalMoves(Square square, Square legalmoves[MAX_LEGALMOVES], int *no_moves)
    {
        *no_moves = 0;

        File file = square.file;
        Rank rank = square.rank;
        Piece p = GetSquare(Square{file, rank});

        if (turn != GetPieceColor(p))
        {
            return mcet::NoErr;
        }

        int i, j;

        // search king
        Piece squares[5][6];
        Piece king = (turn == cWhite) ? WKING : BKING;
        Square kingsq = SearchPiece(king);

        // search checked
        Square checkingPawn,
            checkingKing, checkingKnight, checkingHorizontal, checkingDiagonal;
        int no_checkingPieces = 0;
        Square movableSquares[5]; // the square where 'p' can move if p != king
        PieceType checkingPieceType = PT_EMPTY;
        int no_movableSquares = 0;
        int temp1, temp2;

        if (p != king)
        {
            if ((checkingPawn = IsCheckedByPawn(kingsq, turn)) != SQUAREERR)
            {
                no_checkingPieces++;
                no_movableSquares = 1;
                movableSquares[0] = checkingPawn;
                checkingPieceType = PT_PAWN;
            }
            if ((checkingKing = IsCheckedByKing(kingsq, turn)) != SQUAREERR)
            {
                no_checkingPieces++;
                no_movableSquares = 1;
                movableSquares[0] = checkingKing;
                checkingPieceType = PT_KING;
            }
            if ((checkingKnight = IsCheckedByKnight(kingsq, turn)) != SQUAREERR)
            {
                no_checkingPieces++;
                no_movableSquares = 1;
                movableSquares[0] = checkingKnight;
                checkingPieceType = PT_KNIGHT;
            }
            if ((checkingHorizontal = IsCheckedByHorizontal(kingsq, turn)) != SQUAREERR)
            {
                no_checkingPieces++;
                if (checkingHorizontal.file == kingsq.file)
                {
                    temp1 = (checkingHorizontal.rank > kingsq.rank) ? 1 : -1;
                    for (no_movableSquares = 0; no_movableSquares < abs((int)kingsq.rank - (int)checkingHorizontal.rank); no_movableSquares++)
                    {
                        movableSquares[no_movableSquares] = Square{kingsq.file, kingsq.rank + no_movableSquares * temp1};
                    }
                }
                else
                {
                    temp1 = (checkingHorizontal.file > kingsq.file) ? 1 : -1;
                    for (no_movableSquares = 0; no_movableSquares < abs((int)kingsq.file - (int)checkingHorizontal.file); no_movableSquares++)
                    {
                        movableSquares[no_movableSquares] = Square{kingsq.file + no_movableSquares * temp1, kingsq.rank};
                    }
                }
                checkingPieceType = PT_HORIZONTAL;
            }
            if ((checkingDiagonal = IsCheckedByDiagonal(kingsq, turn)) != SQUAREERR)
            {
                no_checkingPieces++;
                temp1 = (checkingDiagonal.file > kingsq.file) ? 1 : -1;
                temp2 = (checkingDiagonal.rank > kingsq.rank) ? 1 : -1;
                for (no_movableSquares = 0; no_movableSquares < abs((int)kingsq.file - (int)checkingDiagonal.file); no_movableSquares++)
                {
                    movableSquares[no_movableSquares] = Square{
                        kingsq.file + no_movableSquares * temp1, kingsq.rank + no_movableSquares * temp2};
                }
                checkingPieceType = PT_DIAGONAL;
            }

            if (no_checkingPieces >= 2)
            {
                *no_moves = 0;
                return mcet::NoErr;
            }
        }

        MCError err;

        switch (p)
        {
        case WPAWN:
        case BPAWN:
            if (no_checkingPieces == 0)
            {
                // not checked
                return LegalMovesPawn0Checked(this, square, kingsq, legalmoves, no_moves);
            }
            else
            {
                // checked
                return LegalMovesPawn1Checked(this, square, kingsq, legalmoves, no_moves,
                                              movableSquares, no_movableSquares, checkingPieceType);
            }
            break;
        case WKING:
        case BKING:
            return LegalMovesKing(this, square, legalmoves, no_moves);
            break;
        case WQUEEN:
        case BQUEEN:
            break;
        case WBISHOP:
        case BBISHOP:
            break;
        case WKNIGHT:
        case BKNIGHT:
            if (no_checkingPieces == 0)
            {
                // not checked
                return LegalMovesKnight0Checked(this, square, kingsq, legalmoves, no_moves);
            }
            else
            {
                // checked
                return LegalMovesKnight1Checked(this, square, kingsq, legalmoves, no_moves,
                                                movableSquares, no_movableSquares, checkingPieceType);
            }
            break;
        case WROOK:
        case BROOK:
            break;
        }

        return mcet::NoErr;
    }

    // judge whether checked by pawn
    // variable 'king' is the king square, and 'color' is the color
    // return the square of checking king
    Square Board::IsCheckedByPawn(Square king, Color color)
    {
        if (color == ColorErr)
            return SQUAREERR;
        int direction = (color == cWhite) ? 1 : -1;
        Rank first = (color == cWhite) ? RANK1 : RANK6;
        Piece pawn = (color == cWhite) ? BPAWN : WPAWN;
        if (king.rank == first)
        {
            return SQUAREERR;
        }

        if (king.file == AFILE)
        {
            if (GetSquare(Square{BFILE, king.rank + direction}) == pawn)
                return Square{BFILE, king.rank + direction};
        }
        else if (king.file == EFILE)
        {
            if (GetSquare(Square{BFILE, king.rank + direction}) == pawn)
                return Square{BFILE, king.rank + direction};
        }
        else
        {
            if (GetSquare(Square{king.file - 1, king.rank + direction}) == pawn)
                return Square{king.file - 1, king.rank + direction};
            if (GetSquare(Square{king.file + 1, king.rank + direction}) == pawn)
                return Square{king.file + 1, king.rank + direction};
        }

        return SQUAREERR;
    }

    // judge whether checked by king
    // variable 'king' is the "judged" king square, and 'color' is the color
    // return the square of checking king
    Square Board::IsCheckedByKing(Square king, Color color)
    {
        if (color == ColorErr)
            return SQUAREERR;
        int l = -1, r = 1, b = -1, f = 1;
        File file = king.file;
        Rank rank = king.rank;
        Piece ok = (color == cWhite) ? BKING : WKING;

        if (file == AFILE)
            l = 1;
        else if (file == EFILE)
            r = -1;
        if (rank = RANK1)
            b = 1;
        else if (rank == RANK6)
            f = -1;

        int i, j;

        for (i = b; i <= f; i += 2)
        {
            for (j = (l == -1) ? -1 : 0; j <= (r == 1) ? 1 : 0; j++)
            {
                if (GetSquare(Square{file + j, rank + i}) == ok)
                    return Square{file + j, rank + i};
            }
        }
        for (j = l; j <= r; j += 2)
        {
            if (GetSquare(Square{file + j, rank}) == ok)
                return Square{file + j, rank};
        }

        return SQUAREERR;
    }

    // judge whether checked by horizontal pieces (Rook, Queen)
    // variable 'king' is the "judged" king square, and 'color' is the color
    // return the square of checking king
    Square Board::IsCheckedByHorizontal(Square king, Color color)
    {
        if (color == ColorErr)
            return SQUAREERR;
        File lfile, kfile = king.file;
        Rank lrank, krank = king.rank;
        int i;
        Piece q, r, p;

        if (color == cWhite)
        {
            q = BQUEEN;
            r = BROOK;
        }
        else
        {
            q = WQUEEN;
            r = WROOK;
        }

        for (i = -1; i <= 1; i += 2)
        {
            lrank = krank + i;
            lfile = kfile;
            while (RANK1 <= lrank && lrank <= RANK6)
            {
                p = GetSquare(Square{lfile, lrank});
                if (p == q || p == r)
                {
                    return Square{lfile, lrank};
                }
                else if (p != EMPTYSQ)
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
                p = GetSquare(Square{lfile, lrank});
                if (p == q || p == r)
                {
                    return Square{lfile, lrank};
                }
                else if (p != EMPTYSQ)
                {
                    break;
                }
                lfile += i;
            }
        }

        return SQUAREERR;
    }

    // judge whether checked by diagonal pieces (Bishop, Queen)
    // variable 'king' is the "judged" king square, and 'color' is the color
    // return the square of checking king
    Square Board::IsCheckedByDiagonal(Square king, Color color)
    {
        if (color == ColorErr)
            return SQUAREERR;

        File dfile, kfile = king.file;
        Rank drank, krank = king.rank;
        Piece q, b, p;
        int i, j;

        if (color == cWhite)
        {
            q = BQUEEN;
            b = BBISHOP;
        }
        else
        {
            q = WQUEEN;
            b = WBISHOP;
        }

        for (i = -1; i <= 1; i += 2)
        {
            for (j = -1; j <= 1; j += 2)
            {
                drank = krank + i;
                dfile = kfile + j;
                while (RANK1 <= drank && drank <= RANK6 && AFILE <= dfile && dfile <= EFILE)
                {
                    p = GetSquare(Square{dfile, drank});
                    if (p == q || p == b)
                    {
                        return Square{dfile, drank};
                    }
                    else if (p != EMPTYSQ)
                    {
                        break;
                    }
                    drank += i;
                    dfile += j;
                }
            }
        }
    }

    // judge whether checked by knight
    // variable 'king' is the "judged" king square, and 'color' is the color
    // return the square of checking king
    Square Board::IsCheckedByKnight(Square king, Color color)
    {
        if (color != ColorErr)
            return SQUAREERR;

        File nfile, kfile = king.file;
        Rank nrank, krank = king.rank;
        Piece n = (color == cWhite) ? BKNIGHT : WKNIGHT;
        int i, j, k;

        for (i = 0; i <= 1; i++)
        {
            for (j = 0; j <= 1; j++)
            {
                for (k = 0; k <= 1; k++)
                {
                    nfile = kfile + (1 + i) * (2 * j - 1);
                    nrank = krank + (2 - i) * (2 * k - 1);
                    if (GetSquare(Square{nfile, nrank}) == n)
                    {
                        return Square{nfile, nrank};
                    }
                }
            }
        }

        return SQUAREERR;
    }

    // search the specified piece and get all the squares of board
    Square Board::SearchPiece(Piece piece)
    {
        int i, j;

        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 6; j++)
            {
                if (GetSquare(Square{(File)i, (Rank)j}) == piece)
                    return Square{(File)i, (Rank)j};
            }
        }

        return SQUAREERR;
    }

    // check equality between Boards
    bool Board::operator==(const Board &b)
    {
        if (turn != b.turn)
            return false;
        else if (castlingPossibility != b.castlingPossibility)
            return false;
        else if (enpassantAblePawnFile != b.enpassantAblePawnFile)
            return false;

        for (int i = 0; i < 5; i++)
        {
            if (files[i] != b.files[i])
                return false;
        }
        return true;
    }

    bool Board::operator!=(const Board &b) { return !(*this == b); }
}