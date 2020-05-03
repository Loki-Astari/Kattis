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


static constexpr std::size_t bufferSize = 28;
std::vector<char>   data(bufferSize + 1);
char*               buffer  = &data[0];
char*               theend  = buffer;

template<typename...T>
bool getData(char const* format, T... args)
{
    std::size_t size = 0;
    //fprintf(stdout, "Left: %ld, Pre: --->%s<---\n", (theend - buffer), buffer);
    if ((buffer == theend) || (sscanf(buffer, format, args..., &size) != sizeof...(T)) || (buffer + size >= theend))
    {
        //fprintf(stdout, "Size: %lu Before: --->%s<---\n", size, buffer);
        size = theend - buffer;
        std::copy(buffer, buffer + size, &data[0]);
        std::size_t max = fread(&data[size], 1, bufferSize - size, stdin);
        max += size;
        buffer = &data[0];
        buffer[max] = '\0';
        //fprintf(stdout, "Had: %lu Got: %lu Now: --->%s<---\n", size, max, buffer);
        theend = buffer + max;
        if (sscanf(buffer, format, args..., &size) != sizeof...(T)) {
            //fprintf(stdout, "After0: --->%s<---\n", buffer);
            return false;
        }
        //fprintf(stdout, "After1: --->%s<---\n", buffer);
    }
    buffer += size;
    return true;
}

int main()
{
    //std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    std::ios_base::sync_with_stdio(false);
    //    std::cin.tie(nullptr);

    struct T {
        int wins = 0;
        int loss = 0;
    };
    //std::size_t max = fread(&data[0], 1, bufferSize, stdin);
    //fprintf(stdout, "Read: %lu: %c %c\n", max, data[0], data[2]);

    //buffer = &data[0];
    //buffer[max] = '\0';
    //theend = buffer + max;

    char lineBreak[] = "\0";
    while (true)
    {
        int n = 0;
        getData(" %d%n", &n);

        if (n == 0) {
            break;
        }

        int k;
        if (getData(" %d%n", &k))
        {
            std::vector<T> games(n);

            fprintf(stdout, "%s", lineBreak);
            lineBreak[0] = '\n';

            for (int gameCount = (k * n * (n -1))/2; gameCount; --gameCount)
            {
                //fprintf(stdout, "GC: %d\n", gameCount);
                int         p1;
                int         p2;
                char        n1[20];
                char        n2[20];
                //if (sscanf(buffer, " %d %s %d %s%n", &p1, n1, &p2, n2, &size) == 4)
                if (getData(" %d %s %d %s%n", &p1, n1, &p2, n2))
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


