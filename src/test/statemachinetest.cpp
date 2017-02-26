#include <gtest/gtest.h>
#include "../BackTester/statemachine.h"
#include "../BackTester/event.h"
#include "../BackTester/eventqueue.h"
#include "../BackTester/marketevent.h"
#include "../BackTester/ohlcdatapoint.h"
#include "../BackTester/signalevent.h"
#include "../BackTester/strategy.h"
#include "../BackTester/buyandholdstrategy.h"
#include "../BackTester/portfoliohandler.h"
#include <memory>

class StateMachineTest : public ::testing::Test {
public:

    StateMachine machine;
    EventQueue eventQueue;
    OHLCDataPoint datapoint;
    PortfolioHandler portfolio;
    std::unique_ptr<Strategy> strategy = std::make_unique<BuyAndHoldStrategy>();

    StateMachineTest() : datapoint("test", 10, 20, 30, 30, 20, 10) {}

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};


// State is IDLE, when we receive a market event, state should become STRATEGY_CALCULATION
TEST_F (StateMachineTest, IDLE_to_STRATEGYCALCULATION_Transition) {
    EXPECT_EQ(machine.GetCurrentState(), StateMachine::State::IDLE);
    std::unique_ptr<Event> event(std::make_unique<MarketEvent>(datapoint));
    machine.DoTransition(eventQueue, event.get(), strategy.get(), portfolio);
    EXPECT_EQ(machine.GetCurrentState(), StateMachine::State::STRATEGY_CALCULATION);
}

// State is IDLE should not be able to transition when we receive an event which isn't a market event
TEST_F (StateMachineTest, IDLE_to_SIGNALEVENT_Transition) {
    EXPECT_EQ(machine.GetCurrentState(), StateMachine::State::IDLE);
    std::unique_ptr<Event> event(std::make_unique<SignalEvent>("BLMB", SignalEvent::SignalType::LONG, 10.0));
    EXPECT_DEATH(machine.DoTransition(eventQueue, event.get(), strategy.get(), portfolio), "Make sure you have added the transition to the stateTransitions table");
}
