#include "contest.h"
#include "board.h"

int main()
{
    using ThorsAnvil::Contest::Timer;
    using ThorsAnvil::Contest::KnightTour::Board;

    Timer   timer;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Board       board(std::cin);
    //std::cout << "Before:\n";
    //std::cout << board;

    if (board.runTour()) {
        //std::cout << "After :\n";
        std::cout << board;
    }
}


