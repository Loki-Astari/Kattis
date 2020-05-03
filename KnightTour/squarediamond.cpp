#include "squarediamond.h"
#include "board.h"


using namespace ThorsAnvil::Contest::KnightTour;

SquareDiamond::CellRoutePair SquareDiamond::getRoute(int square)
{
    int         cell    = squareToCell(square);
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

bool SquareDiamond::runTourSquare(int currentMove, std::vector<int> const& route, int routePos, int x, int y)
{
    if (!board.validMove(currentMove, x, y)) {
        return false;
    }

    Board::BoardUpdate   update(board, currentMove, x, y);
    if (!update) {
        return false;
    }

    if (routePos != 4)
    {
        int next = route[routePos];
        int newX = (next - 1) % 8;
        int newY = (next - 1) / 8;
        if(runTourSquare(currentMove + 1, route, routePos + 1, newX, newY)) {
            update.setOk();
            return true;
        }
        return false;
    }

    for(auto const& p: pos) {
        int newX = x + std::get<0>(p);
        int newY = y + std::get<1>(p);

        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
            continue;
        }

        if (runTourSquare(currentMove + 1, newX, newY)) {
            update.setOk();
            return true;
        }
    }
    return false;
}

bool SquareDiamond::runTourSquare(int currentMove, int x, int y)
{
    if (currentMove == 65) {
        return true;
    }

    int square = y * 8 + x + 1;
    CellRoutePair routes = getRoute(square);

    return runTourSquare(currentMove, std::get<0>(routes), 1, x, y) || runTourSquare(currentMove, std::get<1>(routes), 1, x, y);
}

