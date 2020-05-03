#include <iostream>
#include <tuple>
#include <iomanip>

class FastInt
{
    int&    val;
    public:
    FastInt(int& v): val(v) {}

    friend std::istream& operator>>(std::istream& str, FastInt const& data)
    {
        auto buf = str.rdbuf();
        int  sign = 1;

        int c;
        while (std::isspace(c = buf->sbumpc()))
        {}

        if (c == '-') {
            sign = -1;
            c = buf->sbumpc();
        }
        data.val = c - '0';
        while (std::isdigit(c = buf->sbumpc())) {
            data.val = (data.val * 10) + (c - '0');
        }
        data.val *= sign;

        return str;
    }
};

class Board
{
    int     row[8] = {0};
    int     col[8] = {0};

    int     board[8][8] = {0};
    int     move[66] = {0};
    int     count = 0;
    static std::pair<int, int> constexpr pos[8] = {{-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}};
    public:
    Board(std::istream& str)
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
                }
            }
        }

    }
    bool runTour()
    {
        return runTour(1, (move[1] - 1) % 8, (move[1] - 1) / 8);
    }
    friend std::ostream& operator<<(std::ostream& str, Board const& data)
    {
        for (int loopX = 0;loopX < 8;++loopX) {
            for (int loopY = 0; loopY < 8;++loopY) {
                str << std::setw(3) << data.board[loopX][loopY] << " ";
            }
            str << " => " << data.col[loopX] << "\n";
        }
        str << "===============================\n";
        for(int loopY = 0; loopY < 8;++loopY) {
            str << std::setw(3) << data.row[loopY] << " ";
        }
        str << "\n\n";
        //std::cerr << "Count: " << data.count << "\n";
        return str;
    }
    private:
    class BoardUpdate
    {
        Board&  parent;
        int     position;
        int     x;
        int     y;
        bool    ok;
        public:
            BoardUpdate(Board& board, int position, int x, int y, bool ok = false)
                : parent(board)
                , position(position)
                , x(x)
                , y(y)
                , ok(ok)
            {
                parent.board[x][y] = position;
                parent.col[y] += position;
                parent.row[x] += position;
            }
            void setOk()
            {
                ok  = true;
            }
            ~BoardUpdate()
            {
                if (!ok) {
                    parent.board[x][y] = -1;
                    parent.col[y] -= position;
                    parent.row[x] -= position;
                }
            }
    };

    bool runTour(int position, int x, int y)
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
            BoardUpdate     update(*this, position, x, y, true);
            return runTour(position + 1, nextSquare % 8, nextSquare / 8);
        }
        else
        //if (((move[position] == 0 || move[position] == y * 8 + x)) && (board[x][y] == -1 || board[x][y] == position))
        {
            if ((move[position] == 0) && ((row[y] + position) > 260 || (col[x] + position) > 260)) {
                return false;
            }
            for (auto const& n: pos) {
                BoardUpdate     update(*this, position, x, y);
                int newX = x + std::get<0>(n);
                int newY = y + std::get<1>(n);
                if (newX < 0 || newX >=8 || newY < 0 || newY >= 8) {
                    continue;
                }
                //std::cout << "POS: " << position << "\n" << (*this) << "\n\n";
                if (runTour(position + 1, newX, newY)) {
                    update.setOk();
                    return true;
                }
            }
        }
        return false;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Board       board(std::cin);
    //std::cout << "Before:\n";
    //std::cout << board;

    if (board.runTour()) {
        //std::cout << "After :\n";
        std::cout << board;
    }
    else {
        //std::cout << "Fail\n";
    }
}

