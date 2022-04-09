#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

class Time
{
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> _started;

    public:
        inline static std::chrono::time_point<std::chrono::high_resolution_clock> Now() { return std::chrono::high_resolution_clock::now(); } 

    public:
        static double Since(Time* time);

    public:
        Time() { _started = Now(); }
        inline std::chrono::time_point<std::chrono::high_resolution_clock> GetStarted() { return _started; }

    public:
        const char* String();
};

#endif
