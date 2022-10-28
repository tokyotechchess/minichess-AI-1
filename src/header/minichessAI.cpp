#include "minichessAI.h"
using std::string;
namespace minichess_AI
{
    namespace
    {
        Square reverse(Square sq)
        {
            return Square{EFILE - (int)sq.file, RANK6 - (int)sq.rank};
        }

        // point
        // RANK, FILE
        double pPawn[6][5] = {
            {0, 0, 0, 0, 0},
            {1.2, 1.35, 1.22, 1.3, 1.41},
            {1.1, 1.11, 1.12, 1.15, 1.16},
            {1, 1.05, 1.05, 1.11, 1.16},
            {0.9, 0.9, 1, 1.1, 1.11},
            {0, 0, 0, 0, 0}};
        double pBishop[6][5] = {
            {2.5, 2.2, 2.6, 2.25, 2.62},
            {2.12, 2.55, 2.22, 2.56, 2.13},
            {2.4, 2.09, 2.4, 2.11, 2.4},
            {2.07, 2.3, 2.12, 2.3, 2.083},
            {2.3, 2.13, 2.3, 1.98, 2.3},
            {2.13, 2.2, 2.09, 2.2, 1.95}};
        double pRook[6][5] = {
            {5.2, 5.21, 5.23, 5.24, 5.23},
            {5.14, 5.11, 5.11, 5.12, 5.15},
            {4.92, 4.95, 5, 5.04, 5.11},
            {4.89, 4.9, 4.95, 4.97, 5.07},
            {4.88, 4.85, 4.91, 4.94, 5.07},
            {4.8, 4.77, 4.81, 4.9, 5.07}};
        double pQueen[6][5] = {
            {9.2, 9.24, 9.24, 9.25, 9.26},
            {9.19, 9.2, 9.19, 9.22, 9.24},
            {9.11, 9.11, 9.22, 9.05, 9.22},
            {9.08, 9.21, 9.05, 9.03, 9.21},
            {9.11, 9.03, 9.01, 9.02, 9.19},
            {8.98, 9, 9.01, 9.01, 9.11}};
        double pKnight[6][5] = {
            {3.04, 3.05, 3.05, 3.06, 3.05},
            {3.04, 3.09, 3.1, 3.09, 3.04},
            {3.05, 3.1, 3.15, 3.08, 3.06},
            {3.04, 3.09, 3.15, 3.07, 3.05},
            {3.05, 3.08, 3.09, 3.08, 3.04},
            {3, 3.01, 3.02, 3.01, 3}};

        double PiecePoint(Piece p, Square sq)
        {
            Color c = GetPieceColor(p);
            Square temp = (c == cWhite) ? sq : reverse(sq);
            double s = (c == cWhite) ? 1 : -1;

            switch (p)
            {
            case WPAWN:
            case BPAWN:
                return s * pPawn[(int)temp.rank][(int)temp.file];
            case WBISHOP:
            case BBISHOP:
                return s * pBishop[(int)temp.rank][(int)temp.file];
            case WROOK:
            case BROOK:
                return s * pRook[(int)temp.rank][(int)temp.file];
            case WQUEEN:
            case BQUEEN:
                return s * pQueen[(int)temp.rank][(int)temp.file];
            case WKNIGHT:
            case BKNIGHT:
                return s * pPawn[(int)temp.rank][(int)temp.file];
            default:
                return 0;
            }
            return 0;
        }
    }

    double minichessAI::tempEvaluator(Board b)
    {
        int f, r;
        double ev = 0;
        Piece p;

        for (f = 0; f < 5; f++)
        {
            for (r = 0; r < 6; r++)
            {
                p = b.GetSquare(Square{(File)f, (Rank)r});
                ev += PiecePoint(p, Square{(File)f, (Rank)r});
            }
        }

        return ev;
    }

    double minichessAI::alphabeta(Board b, double alpha, double beta, int depth, int depthMax)
    {
        Board copy = b;
        double ret;
        Square legalmoves[MAX_LEGALMOVES];
        int no_moves;
        Square legalmove;
        bool promotion_add = true;
        Piece bestPromotion = EMPTYSQ;

        if (depth == depthMax)
        {
            return tempEvaluator(b);
        }
        else
        {

            for (File f = AFILE; f <= EFILE; f++)
            {
                for (Rank r = RANK1; r <= RANK6; r++)
                {
                    b.LegalMoves(Square{f, r}, legalmoves, &no_moves);
                    for (int i = 0; i < no_moves; i++)
                    {
                        legalmove = legalmoves[i];
                        copy = b;
                        switch (b.GetSquare(Square{f, r}))
                        {
                        case WPAWN:
                            if (r == RANK5)
                            {
                                if (promotion_add)
                                {
                                    copy.MoveForce(Square{f, r}, legalmove, WQUEEN);
                                    bestPromotion = WQUEEN;
                                    promotion_add = false;
                                    i--;
                                }
                                else
                                {
                                    copy.MoveForce(Square{f, r}, legalmove, WKNIGHT);
                                    bestPromotion = WKNIGHT;
                                    promotion_add = true;
                                }
                            }
                            else
                            {
                                copy.MoveForce(Square{f, r}, legalmove, EMPTYSQ);
                            }
                            break;
                        case BPAWN:
                            if (r == RANK2)
                            {
                                if (promotion_add)
                                {
                                    copy.MoveForce(Square{f, r}, legalmove, BQUEEN);
                                    bestPromotion = BQUEEN;
                                    promotion_add = false;
                                    i--;
                                }
                                else
                                {
                                    copy.MoveForce(Square{f, r}, legalmove, BKNIGHT);
                                    bestPromotion = BKNIGHT;
                                    promotion_add = true;
                                }
                            }
                            else
                            {
                                copy.MoveForce(Square{f, r}, legalmove, EMPTYSQ);
                            }
                            break;
                        default:
                            copy.MoveForce(Square{f, r}, legalmove, EMPTYSQ);
                        }
                        ret = alphabeta(copy, alpha, beta, depth + 1, depthMax);
                        switch (b.GetTurn())
                        {
                        case cWhite:
                            if (beta <= ret)
                                return ret;
                            else if (alpha < ret)
                            {
                                alpha = ret;
                                bestMoves_from[depth] = Square{f, r};
                                bestMoves_to[depth] = legalmove;
                                bestMovesPromotion[depth] = bestPromotion;
                            }
                            break;
                        case cBlack:
                            if (alpha >= ret)
                                return ret;
                            else if (beta > ret)
                            {
                                beta = ret;
                                bestMoves_from[depth] = Square{f, r};
                                bestMoves_to[depth] = legalmove;
                                bestMovesPromotion[depth] = bestPromotion;
                            }
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            switch (b.GetTurn())
            {
            case cWhite:
                if (copy.GetTurn() == cWhite)
                {
                    if (b.IsChecked(cWhite))
                    {
                        return -100000;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return alpha;
                }
            case cBlack:
                if (copy.GetTurn() == cBlack)
                {
                    if (b.IsChecked(cBlack))
                    {
                        return 100000;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return beta;
                }
            default:
                break;
            }
            return 0;
        }
    }

    double minichessAI::evaluate(Board b)
    {
        now_analyzed = b;
        evaluation = alphabeta(b, -1000000, 1000000, 0, 6);
        return evaluation;
    }

    double minichessAI::GetEvaluation() { return evaluation; }
    Board minichessAI::GetNowAnalyzed() { return now_analyzed; }
    void minichessAI::GetBestMove(Square *from, Square *to, Piece *promotion)
    {
        *from = bestMoves_from[0];
        *to = bestMoves_to[0];
        *promotion = bestMovesPromotion[0];
    }
}