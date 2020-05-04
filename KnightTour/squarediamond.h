#ifndef THORSANVIL_CONTEST_KNIGHTTOUR_SQUAREDIAMOND_H
#define THORSANVIL_CONTEST_KNIGHTTOUR_SQUAREDIAMOND_H

/*
 * This is a heuristic to solve the knight tour.
 * As such it does not always work.
 *
 * If the problem space already has a lot of squares already defined.
 * it is likely to fall outside the scope of the heuristics and cause it
 * to fail quickly.
 *
 * If the problem space is sparse then this algorithm works very well,
 * though not perfectly (as the defined points must fall inside the
 * diamond square patter perfectly).
 *
 * We are using a symmetric already solved version
 * of the knights tour as developed by Dr Roget in 1840.
 *
 * In this solution the board is divided into 4 quarters
 * Each quarter has four routes (each route covers 4 squares).
 * See sd.gif included with this project.
 *
 * So we now have 16 routes (4 routes per quarter). Each can be run forward or backwards.
 *
 * So given a starting point, we run the route forward then backward.
 * At the end we work out what other routes can be reached (A maximum of 7 other routes
 * you can not jump back to the same route all other poisition in the current route
 * will have been used).
 *
 * So this effectively this reduces the problem to 16 vertices.
 * Each vertices is connected to 7 other vertices.
 */

#include <vector>

namespace ThorsAnvil::Contest::KnightTour
{

class Board;
class SquareDiamond
{
    private:
        // Possible moves a knight can move.
        static std::pair<int, int> constexpr pos[8] = {{-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}};

        // The 16 routes.
        // The chessboard is numbered 1-64.
        // Bottom left is 1.
        // Numbers increase by 1 left to right.
        // Numbers increase by 8 bottom to top.
        static int constexpr cells[17][4] = {
            {-1, -1, -1, -1},   // row 0 is invalid and used as spacing.
                                // We index from 1 to make things more logical.
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

        // Map from a chess square to a route.
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

        CellRoutePair getRoute(int square);

        bool runTour(int currentMove, std::vector<int> const& route, int routePos, int x, int y);
        bool runTour(int currentMove, int x, int y);
        bool runTour(int currentMove);
    public:
        SquareDiamond(Board& board)
            : board(board)
        {}
        bool runTour(int x, int y)        {return runTour(1, x, y);}
};

}

#endif
