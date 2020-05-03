#include "board.h"


using namespace ThorsAnvil::Contest::KnightTour;

int cells[17][4] = {
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

int squreToCellData[65] = {
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

int coordToSquare(int x, int y)
{
    return y * 8 + x + 1;
}

int squareToCell(int square)
{
    return squreToCellData[square];
}

using CellRoute     = std::vector<int>;
using CellRoutePair = std::pair<CellRoute, CellRoute>;

CellRoutePair getRoute(int square)
{
    int     cell    = squareToCell(square);
    int*    cellPtr = cells[cell];

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

CellRoutePair getRoute(int x, int y)
{
    return getRoute(coordToSquare(x, y));
}

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
    return runTourSquare(1) || runTour(1);
}

namespace ThorsAnvil::Contest::KnightTour
{
    std::ostream& operator<<(std::ostream& str, Board const& data)
    {
        for (int loopX = 0;loopX < 8;++loopX) {
            for (int loopY = 0; loopY < 8;++loopY) {
                str << std::setw(2) << data.board[loopX][loopY] << " ";
            }
            str << "\n";
        }
        return str;
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

bool Board::runTour(int position, int x, int y)
{
    ++count;
    if (position == 65) {
        return true;
    }

    //std::cout << "P: " << position << "  [" << x << ", " << y << "]\n";
    if (move[position] != 0 && move[position] != (y * 8 + x) + 1) {
        // Pre-defined position and we missed.
        //std::cout << "\t F1\n";
        return false;
    }

    if (move[position] == 0 && board[x][y] != -1) {
        // When searching only overwrite unused squares
        //std::cout << "\t " <<  move[position] << " : " << board[x][y] << "  F2\n";
        return false;
    }

    int nextSquare = move[position + 1];
    if (nextSquare != 0) {
        --nextSquare;
        int newX    = nextSquare % 8;
        int newY    = nextSquare / 8;
        if (std::abs((x - newX) * (y - newY)) != 2) {
            return false;
        }
        BoardUpdate   update(*this, position, x, y);
        //std::cout << "P: " << position << " => " << (position + 1) << " NS: " << nextSquare << " [" << (nextSquare % 8) << ", " << (nextSquare / 8) << "]\n";

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
            int newX = x + std::get<0>(n);
            int newY = y + std::get<1>(n);
            if (newX < 0 || newX >=8 || newY < 0 || newY >= 8) {
                continue;
            }
            if (position != 64 && board[newX][newY] != -1) {
                continue;
            }
            int currQuad = y    / 4 * 2 + x    / 4;
            int nextQuad = newY / 4 * 2 + newX / 4;
            int stage    = ((position - 1) % 4) != 3 ? 0 : 1;
            //next.emplace(priority[stage][currQuad][nextQuad], newX, newY);
            next.emplace(priority[stage][currQuad][nextQuad] + 10 - Warnsdorff[newX][newY], newX, newY);
        }
        BoardUpdate   update(*this, position, x, y);
        for(auto const& n: next) {
            //std::cout << "POS: " << position << "\n" << (*this) << "\n\n";
            if (update && runTour(position + 1, std::get<1>(n), std::get<2>(n))) {
                update.setOk();
                return true;
            }
        }
    }
    return false;
}

bool Board::runTour(int position)
{
    while (move[position + 1] != 0) {
        ++position;
    }

    return runTour(position, (move[position] - 1) % 8, (move[position] - 1) / 8);
}

// ----------

bool Board::runTourSquare(int currentMove)
{
    return runTourSquare(currentMove, (move[currentMove] - 1) % 8, (move[currentMove] - 1) / 8);
}

bool Board::runTourSquare(int currentMove, int x, int y)
{
    if (currentMove == 65) {
        return true;
    }

    int square = y * 8 + x + 1;
    CellRoutePair routes = getRoute(square);

    return runTourSquare(currentMove, std::get<0>(routes), 1, x, y) || runTourSquare(currentMove, std::get<1>(routes), 1, x, y);
}

bool Board::runTourSquare(int currentMove, std::vector<int> const& route, int routePos, int x, int y)
{
    if (move[currentMove] != 0 && move[currentMove] != (y * 8 + x + 1)) {
        return false;
    }

    if (move[currentMove] == 0 && board[x][y] != -1) {
        return false;
    }

    BoardUpdate   update(*this, currentMove, x, y);
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

