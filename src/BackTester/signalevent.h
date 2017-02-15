#ifndef SIGNALEVENT_H
#define SIGNALEVENT_H

#include <chrono>
#include "event.h"
#include <string>

/*
 * Handles an event which is sent by the strategy class
 */
class SignalEvent : public Event
{
public:

    SignalEvent(const std::string& ticker, SignalType signalType) :
        symbol(ticker),
        signal(signalType),
        dateTime(std::chrono::system_clock::now())
    {}

    void DoAction() {}

private:
    std::string symbol;
    SignalType signal;
    std::chrono::time_point<std::chrono::system_clock> dateTime;
};

#endif // SIGNALEVENT_H
