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
    //std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    std::ios_base::sync_with_stdio(false);
    //    std::cin.tie(nullptr);

    struct T {
        int wins = 0;
        int loss = 0;
    };
    std::vector<char>   data(5'000);
    std::size_t max = fread(&data[0], 1, 5'000, stdin);
    //fprintf(stdout, "Read: %lu: %c %c\n", max, data[0], data[2]);

    char* buffer = &data[0];
    buffer[max] = '\0';
    char* theend = buffer + max;
    int   size;

    char lineBreak[] = "\0";
    while (true)
    {
        int n = 0;
        sscanf(buffer, " %d%n", &n, &size);
        buffer += size;

        if (n == 0 || buffer >= theend) {
            break;
        }

        int k;
        if (sscanf(buffer, " %d%n", &k, &size) == 1)
        {
            //fprintf(stdout, "Doing: %d => %d\n", n, k);
            buffer += size;
            std::vector<T> games(n);

            fprintf(stdout, "%s", lineBreak);
            lineBreak[0] = '\n';

            for (int gameCount = (k * n * (n -1))/2; gameCount; --gameCount) {
                //fprintf(stdout, "GC: %d\n", gameCount);
                int         p1;
                int         p2;
                char        n1[20];
                char        n2[20];
                if (sscanf(buffer, " %d %s %d %s%n", &p1, n1, &p2, n2, &size) == 4)
                {
                    //fprintf(stdout, "%d %s V %d %s\n", p1, n1, p2, n2);
                    buffer += size;

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
                    fprintf(stdout, "%.3f\n", (1.0 * numOfWins / numOfGames));
                } else {
                    fprintf(stdout, "-\n");
                }
            }
        }
    }
    //std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    //std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
}

