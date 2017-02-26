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

    SignalEvent(const std::string& ticker, SignalType signalType, double price) :
        Event(Event::EventType::SIGNAL_EVENT),
        symbol(ticker),
        signal(signalType),
        price(price),
        dateTime(std::chrono::system_clock::now())
    {}

    SignalType GetSignalType() { return signal; }

    double GetPrice() { return price; }

    std::string GetSymbol() { return symbol; }

private:
    std::string symbol;
    SignalType signal;
    double price;
    std::chrono::time_point<std::chrono::system_clock> dateTime;
};

#endif // SIGNALEVENT_H
