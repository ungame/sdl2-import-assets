#include "Time.hpp"

#include <chrono>
#include <ctime>
#include <stdlib.h>

double Time::Since(Time* time)
{
    std::chrono::duration<double> elapsed = Now() - time->GetStarted();

    return elapsed.count();
}

const char* Time::String()
{
    std::time_t tt = std::chrono::high_resolution_clock::to_time_t(_started);
    auto lc = localtime(&tt);
    int len = 20;
    char* str = (char*) malloc(sizeof(char) * len);
    strftime(str, len, "%Y-%m-%d %H:%M:%S", lc);
    return str;
}
