#ifndef YAHOOCSVDATAPROVIDER_H
#define YAHOOCSVDATAPROVIDER_H

#include "datahandler.h"

class YahooCSVDataProvider : public DataHandler
{
public:
    YahooCSVDataProvider() = default;

    void UpdateBars();
};

#endif // YAHOOCSVDATAPROVIDER_H
