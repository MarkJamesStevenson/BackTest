#ifndef STRATEGY_H
#define STRATEGY_H

#include <QObject>

class EventQueue;
#include "marketevent.h"
#include <iostream>

class Strategy : public QObject
{
    Q_OBJECT
public:   
    Strategy() = default;

    virtual ~Strategy() = default;

public slots:
    virtual void ProcessMarketEvent(const MarketEvent& marketEvent) = 0;
};

#endif // STRATEGY_H
