#include "timer.h"

void Timer::setSignal(const size_t& flag)
{
    timerSignalFlag = flag;
}

size_t Timer::getSignal()
{
    return timerSignalFlag;
}

void Timer::timerHandler(const boost::system::error_code& /*e*/)
{
    timerSignalFlag = 1;

    timer.expires_at(timer.expires_at() + interval);
    timer.async_wait(boost::bind(&Timer::timerHandler, this, boost::asio::placeholders::error));
}

int Timer::startTimer()
{
    timer.async_wait(boost::bind(&Timer::timerHandler, this, boost::asio::placeholders::error));
    io_service.run();

    return 0;
}

Timer::Timer()
    : interval(periodOfTime)
    , timer(io_service, interval)
{
    periodOfTime  = 100;
    futureStarter = (std::async(std::launch::async, &Timer::startTimer, this));
}

Timer::~Timer()
{
    io_service.stop();
    futureStarter.get();
}