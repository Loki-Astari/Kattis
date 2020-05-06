#ifndef THORSANVIL_CONTEST_H
#define THORSANVIL_CONTEST_H

#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <deque>

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

        if (c == EOF) {
            str.setstate(std::ios::eofbit);
            return str;
        }

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

class Barrier
{
    std::condition_variable             variable;
    int                                 count;
    int                                 waiting;
    public:
        Barrier(int count)
            : count(count)
            , waiting(0)
        {}

        void waitFor(std::unique_lock<std::mutex>& lock)
        {
            waiting = 0;
            variable.wait(lock);
        }

        void checkin(std::unique_lock<std::mutex>& lock)
        {
            waiting++;

            if (waiting != count)
            {
                variable.wait(lock);
            }
            else
            {
                variable.notify_all();
            }
        }
};

class ThreadPool
{
    std::mutex                          mutex;
    std::condition_variable             variable;
    std::vector<std::thread>            threads;
    std::deque<std::function<void()>>   jobs;
    Barrier                             barrier;
    bool                                finished;
    public:
        ThreadPool(int size = 4)
            : barrier(size)
            , finished(false)
        {
            std::unique_lock<std::mutex>   lock(mutex);

            for(int loop = 0; loop < 4; ++loop) {
                threads.emplace_back([&](){threadAction();});
            }
        }
        ~ThreadPool()
        {
            {
                std::unique_lock<std::mutex>   lock(mutex);
                finished = true;
            }
            for(auto& thread: threads) {
                addJob([](){});
            }
            for(auto& thread: threads) {
                thread.join();
            }
        }
        void addJob(std::function<void()>&& action)
        {
            {
                std::unique_lock<std::mutex>   lock(mutex);
                jobs.push_back(std::move(action));
            }
            variable.notify_one();
        }
        void waitForJobsToDrain()
        {
            std::unique_lock<std::mutex>   lock(mutex);
            for(int loop = 0; loop < threads.size(); ++loop) {
                jobs.emplace_back([&](){
                    std::unique_lock<std::mutex>   lock(mutex);
                    barrier.checkin(lock);
                });
            }
            barrier.waitFor(lock);
        }
    private:
        void threadAction()
        {
            while (!finished)
            {
                auto action = getAction();
                action();
            }
        }
        std::function<void()> getAction()
        {
            std::unique_lock<std::mutex>   lock(mutex);
            variable.wait(lock, [&](){return !jobs.empty() || finished;});

            if (finished) {
                return [](){};
            }

            auto result = std::move(jobs.front());
            jobs.pop_front();

            return result;
        }
};

}

#endif
