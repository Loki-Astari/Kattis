#include <iostream>
#include <tuple>
#include <iomanip>
#include <chrono>
#include <set>
#include <tuple>

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
    int     Warnsdorff[8][8] = {0};

    int     board[8][8] = {0};
    int     move[66]    = {0};
    int     count       = 0;
    static std::pair<int, int> constexpr pos[8] = {{-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}};
    static int constexpr priority[2][4][4] = {
        {   {000, 100, 100, 200},
            {100, 000, 200, 100},
            {100, 200, 000, 100},
            {200, 100, 100, 000}
        },
        {   {300, 100, 100, 200},
            {100, 300, 200, 100},
            {100, 200, 300, 100},
            {200, 100, 100, 300}
        }
    };

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
    bool runTour()
    {
        return runTour(1);
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
        /*
        for (int loopX = 0;loopX < 8;++loopX) {
            for (int loopY = 0; loopY < 8;++loopY) {
                str << std::setw(2) << data.Warnsdorff[loopX][loopY] << " ";
            }
            str << " => " << data.col[loopX] <<  "\n";
        }
        */
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
    bool runTour(int position)
    {
        while (move[position + 1] != 0) {
            ++position;
        }

        return runTour(position, (move[position] - 1) % 8, (move[position] - 1) / 8);
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


