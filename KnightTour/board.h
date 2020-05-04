#ifndef THORSANVIL_CONTEST_KNIGHTTOUR_BOARD_H
#define THORSANVIL_CONTEST_KNIGHTTOUR_BOARD_H

#include "../contest.h"

namespace ThorsAnvil::Contest::KnightTour
{

class Board
{
    int     row[8]      = {0};
    int     rowCount[8] = {0};
    int     col[8]      = {0};
    int     colCount[8] = {0};
    int     Warnsdorff[8][8] = {0};

    int     board[8][8] = {0};
    int     move[66]    = {0};

    static std::pair<int, int> constexpr pos[8] = {{-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}};

    public:
        Board(std::istream& str);
        bool runTour();
        void print(std::ostream& str) const;

        friend std::ostream& operator<<(std::ostream& str, Board const& data) {data.print(str);return str;}

        bool validMove(int currentMove, int x, int y) const;
        bool getSquare(int move, int& x, int& y) const;
        bool moveEmpty(int move) const;
        int  getInCount(int x, int y) const;

        class BoardUpdate
        {
            Board&      parent;
            int         position;
            int         x;
            int         y;
            bool        keep;
            bool        valid;
            public:
                BoardUpdate(Board& parent, int position, int x, int y);
                ~BoardUpdate();

                void setOk()                    {keep = true;}
                explicit operator bool() const  {return valid;}
        };
};

}

#endif
