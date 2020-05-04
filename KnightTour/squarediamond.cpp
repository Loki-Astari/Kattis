#include "squarediamond.h"
#include "board.h"

#include <algorithm>


using namespace ThorsAnvil::Contest::KnightTour;

// Given a square
// Find the route and calculate the path forward and backwards.
SquareDiamond::CellRoutePair SquareDiamond::getRoute(int square)
{
    int         cell    = squreToCellData[square];
    int const*  cellPtr = cells[cell];

    auto find   = std::find(cellPtr, cellPtr + 4, square);
    auto offset = find - cellPtr;

    std::vector<int>    r1(4);
    std::vector<int>    r2(4);

    for(int loop = 0; loop < 4; ++loop) {
        r1[loop] = cellPtr[(4 + offset + loop) % 4];
        r2[loop] = cellPtr[(4 + offset - loop) % 4];
    }

    return std::make_pair(r1, r2);
}


bool SquareDiamond::runTour(int currentMove, std::vector<int> const& route, int routePos, int x, int y)
{
    // Make sure the move is basically valid.
    if (!board.validMove(currentMove, x, y)) {
        return false;
    }

    // Update the board.
    Board::BoardUpdate   update(board, currentMove, x, y);
    if (!update) {
        // If this is not a semi-magic board then exit immediately.
        return false;
    }

    if (routePos != 4)
    {
        // We are not at the end of a route
        // So go to the next square in the root.
        int next = route[routePos];
        int newX = (next - 1) % 8;
        int newY = (next - 1) / 8;
        if(runTour(currentMove + 1, route, routePos + 1, newX, newY)) {
            update.setOk();
            return true;
        }
        return false;
    }

    // We are at the end of a route.
    // So try and find the next route to run
    for(auto const& p: pos) {
        int newX = x + std::get<0>(p);
        int newY = y + std::get<1>(p);

        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
            continue;
        }

        if (runTour(currentMove + 1, newX, newY)) {
            update.setOk();
            return true;
        }
    }
    // If no other routes work just returned to false.
    return false;
}

bool SquareDiamond::runTour(int currentMove, int x, int y)
{
    if (currentMove == 65) {
        return true;
    }

    int square = y * 8 + x + 1;
    CellRoutePair routes = getRoute(square);

    return runTour(currentMove, std::get<0>(routes), 1, x, y) || runTour(currentMove, std::get<1>(routes), 1, x, y);
}

