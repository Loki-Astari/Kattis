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
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
#ifndef USE_SCANF
#if 0
    std::locale fast(std::locale::classic(), new SimpleNum);
    std::cin.imbue(fast);
#endif
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif

    std::cout << std::fixed
              << std::setprecision(3);

    struct T {
        int wins = 0;
        int loss = 0;
    };

    char lineBreak[] = "\0";
    while (true)
    {
        int n = 0;
#ifndef USE_SCANF
        std::cin >> n;
#else
        scanf(" %d", &n);
#endif

        if (n == 0) {
            break;
        }

        int k;
#ifndef USE_SCANF
        if (std::cin >> k)
#else
        if (scanf(" %d", &k) == 1)
#endif
        {
            std::vector<T> games(n);

#ifndef USE_SCANF
            std::cout << lineBreak;
#else
            printf("%s", lineBreak);
#endif
            lineBreak[0] = '\n';

            for (int gameCount = (k * n * (n -1))/2; gameCount; --gameCount)
            {
                int         p1;
                int         p2;
                char        n1[20];
                char        n2[20];
#ifndef USE_SCANF
                if (std::cin >> p1 >> n1 >> p2 >> n2)
#else
                if (scanf(" %d %s %d %s", &p1, n1, &p2, n2) == 4)
#endif
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
#ifndef USE_SCANF
                    std::cout << (1.0 * numOfWins / numOfGames) << "\n";
#else
                    printf("%0.3f\n", (1.0 * numOfWins / numOfGames));
#endif
                } else {
#ifndef USE_SCANG
                    std::cout << "-\n";
#else
                    printf("-\n";);
#endif
                }
            }
        }
    }
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::cerr << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
}



