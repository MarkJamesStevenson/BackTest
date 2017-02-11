#include "BackTester/eventqueue.h"
#include <iostream>

int main(int argc, char *argv[])
{
    EventQueue eventQueue;

    std::cout << "HI" << eventQueue.IsEmpty() << std::endl;
}

