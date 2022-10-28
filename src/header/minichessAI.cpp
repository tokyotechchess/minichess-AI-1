#include "minichessAI.h"
using std::string;
namespace minichess_AI
{
    double minichessAI::tempEvaluator(Board b)
    {
        return 0;
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
}