#include "eventloop.h"
#include "dataprovider.h"
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

void EventLoop::Run(DataProvider* dataProvider) const
{
    while (dataProvider->DataAvailable())
    {
        dataProvider->UpdateBars();
        int milliseconds = 300;
        //std::cout << "sleeping for " << milliseconds << " milliseconds" << std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
}

