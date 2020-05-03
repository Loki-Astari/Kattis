#ifndef THORSANVIL_CONTEST_KNIGHTTOUR_SQUAREDIAMOND_H
#define THORSANVIL_CONTEST_KNIGHTTOUR_SQUAREDIAMOND_H

#include "../contest.h"
#include <iostream>
#include <tuple>
#include <iomanip>
#include <set>
#include <tuple>
#include <vector>

namespace ThorsAnvil::Contest::KnightTour
{

class Board;
class SquareDiamond
{
    private:
        static std::pair<int, int> constexpr pos[8] = {{-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}};
        static int constexpr cells[17][4] = {
            {-1, -1, -1, -1},
            { 1, 11, 28, 18},
            { 2, 12, 27, 17},
            { 3, 20, 26,  9},
            { 4, 19, 25, 10},
            { 5, 15, 32, 22},
            { 6, 16, 31, 21},
            { 7, 24, 30, 13},
            { 8, 23, 29, 14},
            {33, 43, 60, 50},
            {34, 44, 59, 49},
            {35, 52, 58, 41},
            {36, 51, 57, 42},
            {37, 47, 64, 54},
            {38, 48, 63, 53},
            {39, 56, 62, 45},
            {40, 55, 61, 46}
        };

        static int constexpr squreToCellData[65] = {
            -1,
             1,  2,  3,  4,  5,  6,  7,  8,
             3,  4,  1,  2,  7,  8,  5,  6,
             2,  1,  4,  3,  6,  5,  8,  7,
             4,  3,  2,  1,  8,  7,  6,  5,
             9, 10, 11, 12, 13, 14, 15, 16,
            11, 12,  9, 10, 15, 16, 13, 14,
            10,  9, 12, 11, 14, 13, 16, 15,
            12, 11, 10,  9, 16, 15, 14, 13
        };

        Board&  board;

        using CellRoute     = std::vector<int>;
        using CellRoutePair = std::pair<CellRoute, CellRoute>;

        int coordToSquare(int x, int y)         {return y * 8 + x + 1;}
        int squareToCell(int square)            {return squreToCellData[square];}
        CellRoutePair getRoute(int x, int y)    {return getRoute(coordToSquare(x, y));};

        CellRoutePair getRoute(int square);
        // ----------
        bool runTourSquare(int currentMove, std::vector<int> const& route, int routePos, int x, int y);
        bool runTourSquare(int currentMove, int x, int y);
        bool runTourSquare(int currentMove);
    public:
        SquareDiamond(Board& board)
            : board(board)
        {}
        bool runTourSquare(int x, int y)        {return runTourSquare(1, x, y);}
};

}

#endif
