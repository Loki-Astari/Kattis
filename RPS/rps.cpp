#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <locale>

static int const result[4][4] = {
    //    p      r   s
    { 0, 0,  1, -1},     // paper
    { 0, 0,  0,  0},
    {-1, 0,  0,  1},     // rock
    { 1, 0, -1,  0}      // scissors
};


static constexpr std::size_t bufferSize = 50'000;
char                data[bufferSize + 1];
char*               buffer  = data;
char*               theend  = buffer;

template<typename...T>
inline
bool getData1(char const* format, T... args)
{
    std::size_t size = 0;
    if ((buffer == theend) || (sscanf(buffer, format, args..., &size) != sizeof...(T)) || (buffer + size >= theend))
    {
        size = theend - buffer;
        std::copy(buffer, buffer + size, data);
        std::size_t max = fread(data + size, 1, bufferSize - size, stdin);
        max += size;
        buffer = data;
        buffer[max] = '\0';
        theend = buffer + max;
        if (sscanf(buffer, format, args..., &size) != sizeof...(T)) {
            return false;
        }
    }
    buffer += size;
    return true;
}

template<typename...T>
inline
bool getData2(char const* format, T... args)
{
    std::size_t size = 0;
    return fscanf(stdin, format, args..., &size) == sizeof...(T);
}

struct FastInt
{
    int&    val;
    FastInt(int& v): val(v){}

    friend std::istream& operator>>(std::istream& str, FastInt const& data)
    {
        char c;
        while (std::isspace(c = str.get()))
        {}

        int val = c - '0';
        for(c = str.get(); std::isdigit(c); c = str.get()) {
            val = val * 10 + (c - '0');
        }
        data.val = val;
        return str;
    }
};
struct FastString
{
    char*    val;
    FastString(char*& v): val(v){}
    template<unsigned int N>
    FastString(char (&v)[N]) :val(v) {}

    friend std::istream& operator>>(std::istream& str, FastString const& data)
    {
        while (std::isspace(data.val[0] = str.get()))
        {}

        int loop = 1;
        for(data.val[loop] = str.get(); !std::isspace(data.val[loop]); ++loop, data.val[loop] = str.get())
        {}
        data.val[loop] = '\0';
        return str;
    }
};

struct SimpleNum: public std::num_get<char>
{
    using iter_type = num_get<char>::iter_type;

    iter_type do_get(iter_type in, iter_type end, std::ios_base& str, std::ios_base::iostate& err, long& val) const override
    {
        val = *in - '0';
        for(++in; in != end && std::isdigit(*in); ++in) {
            val = val * 10 + (*in - '0');
        }
        return in;
    }
};

int main()
{
    //std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    std::locale fast(std::locale::classic(), new SimpleNum);
    std::cin.imbue(fast);
    std::cout.imbue(fast);
    std::cout << std::fixed
              << std::setprecision(3);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);


    struct T {
        int wins = 0;
        int loss = 0;
    };

    char lineBreak[] = "\0";
    while (true)
    {
        int n = 0;
        // getData(" %d%n", &n);
        std::cin >> n;

        if (n == 0) {
            break;
        }

        int k;
        //if (getData(" %d%n", &k))
        if (std::cin >> k)
        {
            std::vector<T> games(n);

            //fprintf(stdout, "%s", lineBreak);
            std::cout << lineBreak;
            lineBreak[0] = '\n';

            for (int gameCount = (k * n * (n -1))/2; gameCount; --gameCount)
            {
                //fprintf(stdout, "GC: %d\n", gameCount);
                int         p1;
                int         p2;
                char        n1[20];
                char        n2[20];
                //if (getData(" %d %s %d %s%n", &p1, n1, &p2, n2))
                if (std::cin >> p1 >> n1 >> p2 >> n2)
                {
                    p1--;
                    p2--;

                    int v = result[n1[0] & 3][n2[0] & 3];

                    if (v != 0)
                    {
                        games[(v == 1) ? p1 : p2].wins++;
                        games[(v == 1) ? p2 : p1].loss++;
                    }
                }
            }

            for (auto const& game: games)
            {
                int numOfWins  = game.wins;
                int numOfGames = game.wins + game.loss;
                if (numOfGames != 0) {
                    //fprintf(stdout, "%.3f\n", (1.0 * numOfWins / numOfGames));
                    std::cout << (1.0 * numOfWins / numOfGames) << "\n";
                } else {
                    //fprintf(stdout, "-\n");
                    std::cout << "-\n";
                }
            }
        }
    }
    //std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    //std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
}



