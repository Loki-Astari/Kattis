#include "bruteforce.h"
#include "board.h"


using namespace ThorsAnvil::Contest::KnightTour;


bool BruteForce::runTour(int position, int x, int y)
{
    if (position == 65) {
        return true;
    }

    if (!board.validMove(position, x, y)) {
        return false;
    }

    int newX = 0;
    int newY = 0;

    if (board.getSquare(position + 1, newX, newY)) {
        if (std::abs((x - newX) * (y - newY)) != 2) {
            return false;
        }
        Board::BoardUpdate   update(board, position, x, y);

        if (update && runTour(position + 1)) {
            update.setOk();
            return true;
        }
        return false;;
    }
    else
    {
        std::set<std::tuple<int, int, int>>    next;
        for (auto const& n: pos) {
            newX = x + std::get<0>(n);
            newY = y + std::get<1>(n);
            if (newX < 0 || newX >=8 || newY < 0 || newY >= 8) {
                continue;
            }
            next.emplace(board.getInCount(newX, newY), newX, newY);
        }
        Board::BoardUpdate   update(board, position, x, y);
        for(auto const& n: next) {
            if (update && runTour(position + 1, std::get<1>(n), std::get<2>(n))) {
                update.setOk();
                return true;
            }
        }
    }
    return false;
}

bool BruteForce::runTour(int position)
{
    int     newX;
    int     newY;
    while (!board.getSquare(position + 1, newX, newY)) {
        ++position;
    }

    return runTour(position, newX, newY);
}

