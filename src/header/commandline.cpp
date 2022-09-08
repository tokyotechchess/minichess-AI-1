#include "commandline.h"

namespace minichess_AI
{
    MCError CommandLine::DisplayBoard(Board *b)
    {
        std::cout << '--|-----------';
        std::cout << '  | a b c d e';
        std::cout << '--|-----------';
        for (Rank r = RANK6; r >= RANK1; r--)
        {
            std::cout << (*b).GetSquare(Square{Square{AFILE, RANK1}});
        }
    }
}
