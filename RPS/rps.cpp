#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>


static int const result[4][4] = {
    //    p      r   s
    { 0, 0,  1, -1},     // paper
    { 0, 0,  0,  0},
    {-1, 0,  0,  1},     // rock
    { 1, 0, -1,  0}      // scissors
};


int main()
{
     std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    std::ios_base::sync_with_stdio(false);
#ifndef NO_TIE
    std::cin.tie(nullptr);
#endif

    struct T {
        int wins = 0;
        int loss = 0;
    };


    char lineBreak[] = "\0";
    while (true)
    {
        int n = 0;
#ifdef USE_SCANF
        fscanf(stdin, " %d", &n);
#else
        std::cin >> n;
#endif

        if (n == 0) {
            break;
        }

        int k;
#ifdef USE_SCANF
        if (fscanf(stdin, " %d", &k) == 1)
#else
            if (std::cin >> k)
#endif
            {
                std::vector<T> games(n);

                std::cout << lineBreak;
                lineBreak[0] = '\n';

                for (int gameCount = (k * n * (n -1))/2; gameCount; --gameCount) {
                    int         p1;
                    int         p2;
#ifdef USE_SCANF
                    char        n1[20];
                    char        n2[20];
                    if (fscanf(stdin, " %d %s %d %s", &p1, n1, &p2, n2) == 4)
#else
                    std::string n1;
                    std::string n2;

                    if (std::cin >> p1 >> n1 >> p2 >> n2)
#endif
                    {
                        p1--;
                        p2--;

                        int v = result[n1[0] & 3][n2[0] & 3];
                        //std::cout << p1 << " " << n1 << " V " << p2 << " " << n2 << " => " << v << "\n";

                        if (v != 0)
                        {
                            games[(v == 1) ? p1 : p2].wins++;
                            games[(v == 1) ? p2 : p1].loss++;
                        }
                    }
                }

                std::cout << std::fixed;
                std::cout << std::setprecision(3);
                for (auto const& game: games)
                {
                    int numOfWins  = game.wins;
                    int numOfGames = game.wins + game.loss;
                    if (numOfGames != 0) {
                        std::cout << (1.0 * numOfWins / numOfGames) << "\n";
                    } else {
                        std::cout << "-\n";
                    }
                }
            }
    }
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
}
