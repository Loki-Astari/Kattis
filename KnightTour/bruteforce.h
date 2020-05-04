#ifndef THORSANVIL_CONTEST_KNIGHTTOUR_BRUTEFORCE_H
#define THORSANVIL_CONTEST_KNIGHTTOUR_BRUTEFORCE_H

#include <utility>

namespace ThorsAnvil::Contest::KnightTour
{

class Board;
class BruteForce
{
    private:
        Board&  board;

        static std::pair<int, int> constexpr pos[8] = {{-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}};
    public:
        BruteForce(Board& board)
            : board(board)
        {}
        bool runTour(int x, int y)        {return runTour(1, x, y);}
    private:
        bool runTour(int position, int x, int y);
        bool runTour(int position);
};

}

#endif
