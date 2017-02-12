#ifndef YAHOOCSVDATAPROVIDER_H
#define YAHOOCSVDATAPROVIDER_H

#include "dataprovider.h"

class YahooCSVDataProvider : public DataProvider
{
public:
    YahooCSVDataProvider() = default;

    void UpdateBars() override;
};

#endif // YAHOOCSVDATAPROVIDER_H
