#include <gtest/gtest.h>
#include <memory>
#include <iostream>
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

TEST (EventQueue, AddEvent) {
    std::unique_ptr<IEvent> event = std::make_unique<MarketEvent>();
    EventQueue eventQueue;
    eventQueue.AddEvent(std::move(event));
    EXPECT_FALSE(eventQueue.IsEmpty());
    std::unique_ptr<IEvent> event2 = eventQueue.GetNextEvent();
    EXPECT_EQ(event2->GetEventType(), IEvent::Event_Type::MARKET_EVENT);
    EXPECT_TRUE(eventQueue.IsEmpty());
}

TEST (EventQueue, AddMultipleEvents) {
    std::unique_ptr<IEvent> event1 = std::make_unique<MarketEvent>();
    std::unique_ptr<IEvent> event2 = std::make_unique<FillEvent>();
    std::unique_ptr<IEvent> event3 = std::make_unique<OrderEvent>();
    std::unique_ptr<IEvent> event4 = std::make_unique<SignalEvent>();
    EventQueue eventQueue;
    eventQueue.AddEvent(std::move(event1));
    eventQueue.AddEvent(std::move(event2));
    eventQueue.AddEvent(std::move(event3));
    eventQueue.AddEvent(std::move(event4));
    EXPECT_FALSE(eventQueue.IsEmpty());
    std::unique_ptr<IEvent> gotEvent1 = eventQueue.GetNextEvent();
    EXPECT_EQ(gotEvent1->GetEventType(), IEvent::Event_Type::MARKET_EVENT);
    std::unique_ptr<IEvent> gotEvent2 = eventQueue.GetNextEvent();
    EXPECT_EQ(gotEvent2->GetEventType(), IEvent::Event_Type::FILL_EVENT);
    std::unique_ptr<IEvent> gotEvent3 = eventQueue.GetNextEvent();
    EXPECT_EQ(gotEvent3->GetEventType(), IEvent::Event_Type::ORDER_EVENT);
    std::unique_ptr<IEvent> gotEvent4 = eventQueue.GetNextEvent();
    EXPECT_EQ(gotEvent4->GetEventType(), IEvent::Event_Type::SIGNAL_EVENT);
    ASSERT_TRUE(eventQueue.IsEmpty());
}
