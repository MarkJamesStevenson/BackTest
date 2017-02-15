#include <gtest/gtest.h>
#include <memory>
#include "../BackTester/eventqueue.h"
#include "../BackTester/marketevent.h"
#include "../BackTester/signalevent.h"
#include "../BackTester/orderevent.h"
#include "../BackTester/fillevent.h"
#include "../BackTester/ievent.h"

TEST (EventQueue, EmptyQueue) {
    EventQueue eventQueue;
    EXPECT_TRUE(eventQueue.IsEmpty());
}

TEST (EventQueue, TryToGetNextEventWithEmptyQueue) {
    EventQueue eventQueue;
    ASSERT_DEATH(auto event = eventQueue.GetNextEvent(), "Should not call with empty queue");
}

TEST (EventQueue, AddEvent) {
    OHLCDataPoint data("date",10, 5, 15, 20, 50, 10);
    auto event = std::make_unique<MarketEvent>(data);
    EventQueue eventQueue;
    eventQueue.AddEvent(std::move(event));
    EXPECT_FALSE(eventQueue.IsEmpty());
    std::unique_ptr<IEvent> event2 = eventQueue.GetNextEvent();
    EXPECT_EQ(event2->GetEventType(), IEvent::Event_Type::MARKET_EVENT);
    EXPECT_TRUE(eventQueue.IsEmpty());
}

TEST (EventQueue, AddMultipleEvents) {
    OHLCDataPoint data("date",10, 5, 15, 20, 50, 10);
    auto event1 = std::make_unique<MarketEvent>(data);
    auto event2 = std::make_unique<FillEvent>("BLMB", "LSE", 10, IEvent::Direction::BUY, 30.4, [] ()
    {
        return 19.0;
    });
    auto event3 = std::make_unique<OrderEvent>("BLMB", IEvent::OrderType::LIM, 10, IEvent::Direction::SELL);
    auto event4 = std::make_unique<SignalEvent>("BLMB", IEvent::SignalType::LONG);
    EventQueue eventQueue;
    eventQueue.AddEvent(std::move(event1));
    eventQueue.AddEvent(std::move(event2));
    eventQueue.AddEvent(std::move(event3));
    eventQueue.AddEvent(std::move(event4));
    EXPECT_FALSE(eventQueue.IsEmpty());
    auto gotEvent1 = eventQueue.GetNextEvent();
    EXPECT_EQ(gotEvent1->GetEventType(), IEvent::Event_Type::MARKET_EVENT);
    auto gotEvent2 = eventQueue.GetNextEvent();
    EXPECT_EQ(gotEvent2->GetEventType(), IEvent::Event_Type::FILL_EVENT);
    auto gotEvent3 = eventQueue.GetNextEvent();
    EXPECT_EQ(gotEvent3->GetEventType(), IEvent::Event_Type::ORDER_EVENT);
    auto gotEvent4 = eventQueue.GetNextEvent();
    EXPECT_EQ(gotEvent4->GetEventType(), IEvent::Event_Type::SIGNAL_EVENT);
    ASSERT_TRUE(eventQueue.IsEmpty());
}

