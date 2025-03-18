#ifndef __CHRONO
#define __CHRONO

#include <chrono>

class Chrono{
    public:
       Chrono();
       void start();
       void stop();
       double time() const;
    private:
       std::chrono::time_point<std::chrono::steady_clock> begin;
       std::chrono::time_point<std::chrono::steady_clock> end;       
};

#endif
