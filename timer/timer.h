#pragma once
#include "../headers/headers.h"
#include <atomic>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <future>

class Timer
{
public:
    Timer();
    ~Timer();
    void   setSignal(const size_t& flag);
    size_t getSignal();

private:
    void timerHandler(const boost::system::error_code& /*e*/);
    int  startTimer();

    std::future<int>                futureStarter;
    boost::asio::io_service         io_service;
    long                            periodOfTime;
    boost::posix_time::milliseconds interval;
    boost::asio::deadline_timer     timer;
    std::atomic<int>                timerSignalFlag;
};