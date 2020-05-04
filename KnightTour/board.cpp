#include "board.h"
#include "squarediamond.h"
#include "bruteforce.h"


using namespace ThorsAnvil::Contest::KnightTour;


Board::Board(std::istream& str)
{
    for(int loopX = 0;loopX < 8;++loopX) {
        for(int loopY = 0;loopY < 8;++loopY) {
            int value;
            str >> FastInt(value);
            board[loopX][loopY] = value;
            if (value != -1) {
                move[value] = loopY * 8 + loopX + 1;
                row[loopY] += value;
                col[loopX] += value;
                ++rowCount[loopY];
                ++colCount[loopX];
            }
        }
    }
    for(int loopX = 0;loopX < 8;++loopX) {
        for(int loopY = 0;loopY < 8;++loopY) {
            if (board[loopX][loopY] != -1) {
                continue;
            }
            for(auto const& p: pos) {
                int newX = loopX + std::get<0>(p);
                int newY = loopY + std::get<1>(p);

                if (newX < 0 || newX >= 8 || newY < 0 || newY >=8) {
                    continue;
                }

                if (board[newX][newY] == -1) {
                    ++Warnsdorff[newX][newY];
                }
            }
        }
    }
}

bool Board::runTour()
{
    SquareDiamond   sd(*this);
    BruteForce      bf(*this);

    int x = (move[1] - 1) % 8;
    int y = (move[1] - 1) / 8;

    return sd.runTourSquare(x, y) || bf.runTour(x, y);
}

void Board::print(std::ostream& str) const
{
    for (int loopX = 0;loopX < 8;++loopX) {
        for (int loopY = 0; loopY < 8;++loopY) {
            str << std::setw(2) << board[loopX][loopY] << " ";
        }
        str << "\n";
    }
}

Board::BoardUpdate::BoardUpdate(Board& parent, int position, int x, int y)
    : parent(parent)
    , position(position)
    , x(x)
    , y(y)
    , keep(true)
    , valid(true)
{/*
    Minimum
    n                                                     n*(n-1)
    1   0                                       p               0
    2   0 + 2                                   2p  + 2         2
    3   0 + 2 + 4                               3p  + 6         6
    4   0 + 2 + 4 + 6                           4p  + 12        12
    5   0 + 2 + 4 + 6 + 8                       5p  + 20        20
    6   0 + 2 + 4 + 6 + 8 + 10                  6p  + 30        30
    7   0 + 2 + 4 + 6 + 8 + 10 + 12             7p  + 42        42
    8   0 + 2 + 4 + 6 + 8 + 10 + 12 +14         8p  + 56        56

    Maximum
                                                (n-1)*(n-2)
    1   p                                       0
    2   p + 1.64                                0
    3   p + 2.64 - 2                            2
    4   p + 3.64 - 6                            6
    5   p + 4.64 - 12                           12
    6   p + 5.64 - 20                           20
    7   p + 6.64 - 30                           30
    8   p + 7.64 - 42                           42
*/
    if (parent.move[position] == 0) {

        int n;
        n = (8 - parent.rowCount[y]);
        int yMin    = n * position + n * (n - 1);
        int yMax    = position + (n - 1)*64 - (n - 1)*(n - 2);

        n  = (8 - parent.colCount[x]);
        int xMin    = n * position + n * (n - 1);
        int xMax    = position + (n - 1)*64 - (n - 1)*(n - 2);

        if ((parent.row[y] + yMin) > 260 || (parent.row[y] + yMax) < 260 || (parent.col[x] + xMin) > 260 || (parent.col[x] + xMax) < 260)
        {
            valid = false;
        }
        else
        {
            parent.board[x][y] = position;
            parent.row[y]  += position;
            parent.col[x]  += position;
            ++parent.rowCount[y];
            ++parent.colCount[x];
            keep  = false;

            for(auto const& p: pos) {
                int newX = x + std::get<0>(p);
                int newY = y + std::get<1>(p);

                if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
                    continue;
                }

                --parent.Warnsdorff[newX][newY];
            }
        }
    }
}

Board::BoardUpdate::~BoardUpdate()
{
    if (!keep)
    {
        parent.board[x][y] = -1;
        parent.row[y]  -= position;
        parent.col[x]  -= position;
        --parent.rowCount[y];
        --parent.colCount[x];

        for(auto const& p: pos) {
            int newX = x + std::get<0>(p);
            int newY = y + std::get<1>(p);

            if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
                continue;
            }

            ++parent.Warnsdorff[newX][newY];
        }
    }
}

bool Board::validMove(int currentMove, int x, int y) const
{
    if (move[currentMove] != 0 && move[currentMove] != (y * 8 + x + 1)) {
        // Pre-defined position and we missed.
        return false;
    }

    if (move[currentMove] == 0 && board[x][y] != -1) {
        // When searching only overwrite unused squares
        return false;
    }

    return true;
}

bool Board::getSquare(int checkMove, int& x, int& y) const
{
    int nextSquare = move[checkMove];
    if (nextSquare != -1) {
        x = (nextSquare - 1) % 8;
        y = (nextSquare - 1) / 8;
    }
    return nextSquare == -1;
}

bool Board::moveEmpty(int checkMove) const
{
    return move[checkMove] != -1;
}

int Board::getInCount(int x, int y) const
{
    return Warnsdorff[x][y];
}

