#include <gtest/gtest.h>
#include <memory>
#include <iostream>
#include "../BackTester/eventqueue.h"
#include "../BackTester/marketevent.h"
#include "../BackTester/ievent.h"

TEST (EventQueue, EmptyQueue) {
    EventQueue eventQueue;
    ASSERT_TRUE(eventQueue.IsEmpty());
}

TEST (EventQueue, AddEvent) {
    std::unique_ptr<IEvent> event = std::make_unique<MarketEvent>();
    EventQueue eventQueue;
    eventQueue.AddEvent(std::move(event));
    ASSERT_FALSE(eventQueue.IsEmpty());
}
