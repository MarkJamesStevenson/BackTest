#include <gtest/gtest.h>
#include <memory>
#include <iostream>
#include "../BackTester/eventqueue.h"
#include "../BackTester/marketevent.h"
#include "../BackTester/ievent.h"
#include "../BackTester/eventhandle.h"

TEST (EventQueue, EmptyQueue) {
    EventQueue eventQueue;
    ASSERT_TRUE(eventQueue.IsEmpty());
}

TEST (EventQueue, AddEvent) {
    EventHandle event(IEvent::Event_Type::MARKET_EVENT);
    EventQueue eventQueue;
    eventQueue.AddEvent(std::move(event));
    ASSERT_FALSE(eventQueue.IsEmpty());
    ASSERT_EQ(eventQueue.GetNextEvent().GetEventType(), IEvent::Event_Type::MARKET_EVENT);
    ASSERT_TRUE(eventQueue.IsEmpty());
}

TEST (EventQueue, AddMultipleEvents) {
    EventHandle event1(IEvent::Event_Type::FILL_EVENT);
    EventHandle event2(IEvent::Event_Type::ORDER_EVENT);
    EventHandle event3(IEvent::Event_Type::MARKET_EVENT);
    EventQueue eventQueue;
    eventQueue.AddEvent(std::move(event1));
    eventQueue.AddEvent(std::move(event2));
    eventQueue.AddEvent(std::move(event3));
    ASSERT_FALSE(eventQueue.IsEmpty());
    ASSERT_EQ(eventQueue.GetNextEvent().GetEventType(), IEvent::Event_Type::FILL_EVENT);
    ASSERT_EQ(eventQueue.GetNextEvent().GetEventType(), IEvent::Event_Type::ORDER_EVENT);
    ASSERT_EQ(eventQueue.GetNextEvent().GetEventType(), IEvent::Event_Type::MARKET_EVENT);
    ASSERT_TRUE(eventQueue.IsEmpty());
}

