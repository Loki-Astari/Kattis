#ifndef THORSANVIL_CONTEST_H
#define THORSANVIL_CONTEST_H

#include <chrono>
#include <iostream>

namespace ThorsAnvil::Contest
{

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

class FastString
{
    char*   val;
    public:
        FastString(char* v): val(v) {}

        friend std::istream& operator>>(std::istream& str, FastString const& data)
        {
            std::istream::sentry sentry(str);
            auto buf = str.rdbuf();

            int c;/*
            while (std::isspace(c = buf->sbumpc()))
            {}*/

            data.val[0] = c;
            int loop = 1;
            for (;!std::isspace(c = buf->sbumpc()); ++loop) {
                data.val[loop] = c;
            }
            data.val[loop] = '\0';
            //std::cerr << "Got: " << data.val << "\n";

            return str;
        }
};

}

#endif
