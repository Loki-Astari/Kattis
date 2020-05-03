#include <iostream>
#include <tuple>
#include <iomanip>
#include <chrono>

class Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    public:
        Timer()
            : start(std::chrono::high_resolution_clock::now())
        {}
        ~Timer()
        {
            std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
            std::cerr << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "\n";
        }
};

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
    int     row[8]      = {0};
    int     rowCount[8] = {0};
    int     col[8]      = {0};
    int     colCount[8] = {0};

    int     board[8][8] = {0};
    int     move[66]    = {0};
    int     count       = 0;
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
                    ++rowCount[loopY];
                    ++colCount[loopX];
                }
            }
        }

    }
    bool runTour()
    {
        return runTour(0, 0);
    }
    friend std::ostream& operator<<(std::ostream& str, Board const& data)
    {
        for (int loopX = 0;loopX < 8;++loopX) {
            for (int loopY = 0; loopY < 8;++loopY) {
                str << std::setw(2) << data.board[loopX][loopY] << " ";
            }
            str << /*" => " << data.col[loopX] << */ "\n";
        }
        /*
           str << "===============================\n";
           for(int loopY = 0; loopY < 8;++loopY) {
           str << std::setw(3) << data.row[loopY] << " ";
           }
           str << "\n\n";
         */
        //std::cerr << "Count: " << data.count << "\n";
        return str;
    }
    private:
    class BoardUpdate
    {
        Board&      parent;
        int         position;
        int         x;
        int         y;
        bool        keep;
        bool        valid;
        public:
            BoardUpdate(Board& parent, int position, int x, int y)
                : parent(parent)
                , position(position)
                , x(x)
                , y(y)
                , keep(true)
                , valid(true)
            {
                if ((parent.row[y] + position) > 260 || (parent.col[x] + position) > 260)
                {
                    valid = false;
                }
                else
                {
                    parent.board[x][y] = position;
                    parent.move[position] = y * 8 + x + 1;
                    parent.row[y]  += position;
                    parent.col[x]  += position;
                    ++parent.rowCount[y];
                    ++parent.colCount[x];
                    keep  = false;
                }
            }
            void setOk()
            {
                keep = true;
            }
            explicit operator bool()
            {
                return valid;
            }
            ~BoardUpdate()
            {
                if (!keep)
                {
                    parent.board[x][y] = -1;
                    parent.move[position] = 0;
                    parent.row[y]  -= position;
                    parent.col[x]  -= position;
                    --parent.rowCount[y];
                    --parent.colCount[x];
                }
            }
    };
    bool runTour(int loopX, int loopY)
    {
        if (loopY == 8) {
            loopY = 0;
            ++loopX;
        }
        if (loopX == 8) {
            return true;
        }
        //std::cout << "K: " << loopX << ", " << loopY << "\n";

        if (board[loopX][loopY] != -1) {
            return runTour(loopX, loopY+1);
        }
        else {
            for(int p = 1; p < 65; ++p) {
                if (move[p] != 0) {
                    continue;
                }
                BoardUpdate     update(*this, p, loopX, loopY);
                if (update && runTour(loopX, loopY + 1)) {
                    update.setOk();
                    return true;
                }
            }
            return false;
        }
    }
};

int main()
{
    Timer   timer;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Board       board(std::cin);
    //std::cout << "Before:\n";
    //std::cout << board;

    if (board.runTour()) {
        //std::cout << "After :\n";
        std::cout << board;
    }
}


