#include "Timer.hpp"

Timer::Timer(double timeGap): checkPoint(clock()), timeGap(timeGap)
{

}
Timer::~Timer()
{

}

void Timer::resetTimer()
{
    checkPoint = clock();
}
void Timer::setTimeGap(double timeGap)
{
    this->timeGap = timeGap;
}
bool Timer::exceedTimeGap()
{
    return (static_cast<double>(clock() - checkPoint) / CLK_TCK >= timeGap);
}
