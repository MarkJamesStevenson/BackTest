#include "marketevent.h"

std::ostream& operator<<(std::ostream& os, const MarketEvent& event)
{
    os << "Market data received:\n"
       << " Date: "         << event.dataPoint.date
       << " Open: "         << event.dataPoint.open
       << " High: "         << event.dataPoint.high
       << " Low: "          << event.dataPoint.low
       << " Close: "        << event.dataPoint.close
       << " Volume: "       << event.dataPoint.volume
       << " Adjusted Close "<< event.dataPoint.adjClose;
    return os;
}
