#include "eventloop.h"
#include "dataprovider.h"

void EventLoop::Run() const
{
    myTimer->start(1);
}

void EventLoop::run2() const
{
    if (dataProvider->DataAvailable())
    {
        dataProvider->UpdateBars();
    }
    else
    {
        myTimer->stop();
        emit EventLoopCompleted();
    }
}

