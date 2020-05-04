#include "bruteforce.h"
#include "board.h"

#include <set>
#include <tuple>


using namespace ThorsAnvil::Contest::KnightTour;


bool BruteForce::runTour(int position, int x, int y)
{
    // If we get to 65 then we have completed
    if (position == 65) {
        return true;
    }

    // Make sure the current spot is valid.
    if (!board.validMove(position, x, y)) {
        return false;
    }

    int newX = 0;
    int newY = 0;

    if (board.getSquare(position + 1, newX, newY)) {

        // The next spot is already decided.
        // Make sure it can be reached from the current spot.
        if (std::abs((x - newX) * (y - newY)) != 2) {
            return false;
        }

        // Update the board with the current spot.
        Board::BoardUpdate   update(board, position, x, y);

        // Check the update worked then continue with the next
        // move. Note the next move is already determined.
        if (update && runTour(position + 1)) {
            update.setOk();
            return true;
        }
    }
    else
    {
        // The next spot is not decided.
        // So we calculate a list of possible valid moves.
        // These moves are put in the set `next` which is order
        // to try and achieve a best ordering based on `Warnsdorff` rule.
        // Google it.
        std::set<std::tuple<int, int, int>>    next;
        for (auto const& n: pos) {
            newX = x + std::get<0>(n);
            newY = y + std::get<1>(n);
            if (newX < 0 || newX >=8 || newY < 0 || newY >= 8) {
                continue;
            }
            next.emplace(board.getInCount(newX, newY), newX, newY);
        }

        // Update the board with the current spot
        // Then try all the moves until we find a working move.
        Board::BoardUpdate   update(board, position, x, y);
        for(auto const& n: next) {
            if (update && runTour(position + 1, std::get<1>(n), std::get<2>(n))) {
                update.setOk();
                return true;
            }
        }
    }
    // If we have not returned then this moved failed so return false
    // to unwind the brute force attack one level.
    // Note the `update` destructor will remove the move.
    return false;
}

bool BruteForce::runTour(int position)
{
    /*
     * While we know what the next square
     * i.e the puzzle specified the position of the next move
     *
     * Then we simply advance (no need to do brute force work)
     */
    int     newX;
    int     newY;
    while (!board.getSquare(position + 1, newX, newY)) {
        ++position;
    }

    // We need to calculate the next move.
    return runTour(position, newX, newY);
}

