#include <ostream>
#include "orderevent.h"

std::ostream& operator<<(std::ostream& os, const OrderEvent& event)
{
    std::string type = event.orderType == OrderEvent::OrderType::MKT ?
                "MKT" : "LIM";
    std::string direction = event.direction == OrderEvent::Direction::BUY ?
                "BUY" : "SELL";
    os << "Order:"
       << " Symbol="     << event.symbol
       << " Order type=" << type
       << " Quantity="   << event.quantity
       << " Direction="  << direction;
    return os;
}
