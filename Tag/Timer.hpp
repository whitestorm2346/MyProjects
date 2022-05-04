#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED

#include <ctime>

class Timer
{
private:
    clock_t checkPoint;
    double timeGap;

public:
    Timer(double timeGap = 1.0);
    virtual ~Timer();

    void resetTimer();
    void setTimeGap(double timeGap);
    bool exceedTimeGap();
};

#endif // TIMER_HPP_INCLUDED
