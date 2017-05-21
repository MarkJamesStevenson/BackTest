#include "marketevent.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const MarketEvent& event)
{
    os << "Market data received:\n"
       << " Date: "         << event.dataPoint.date.toString("dd MMMM yyyy").toStdString()
       << " Open: "         << event.dataPoint.open
       << " High: "         << event.dataPoint.high
       << " Low: "          << event.dataPoint.low
       << " Close: "        << event.dataPoint.close
       << " Volume: "       << event.dataPoint.volume
       << " Adjusted Close "<< event.dataPoint.adjClose;
    return os;
}
