#ifndef YAHOOCSVDATAPROVIDER_H
#define YAHOOCSVDATAPROVIDER_H

#include "dataprovider.h"
#include <string>
#include "curl/curl.h"

class YahooCSVDataProvider : public DataProvider
{
public:
    YahooCSVDataProvider() = default;

    void Initialise(const std::string& symbol) override;

    void UpdateBars() override;

private:
    std::string ConstructUrl(const std::string& symbol,
                             int fromMonth,
                             int fromDay,
                             int fromYear,
                             int toMonth,
                             int toDay,
                             int toYear,
                             char tradingPeriod);
};

#endif // YAHOOCSVDATAPROVIDER_H
