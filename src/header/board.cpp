#include "board.h"

namespace minichess_AI
{
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

    MCError Board::MoveForce(Square from_square, Square to_square, Piece promotion_piece)
    {
        
    }

    bool Board::operator!=(const Board &b) { return !(*this == b); }
}
