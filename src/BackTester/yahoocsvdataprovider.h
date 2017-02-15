#ifndef YAHOOCSVDATAPROVIDER_H
#define YAHOOCSVDATAPROVIDER_H

#include "dataprovider.h"
#include <string>
#include <vector>
#include "curl/curl.h"

class YahooCSVDataProvider : public DataProvider
{
public:
    YahooCSVDataProvider() = default;

    enum class Month {
        JANUARY = 0,
        FEBRUARY,
        MARCH,
        APRIL,
        MAY,
        JUNE,
        JULY,
        AUGUST,
        SEPTEMBER,
        OCTOBER,
        NOVEMBER,
        DECEMBER
    };

    enum class TradingPeriod {
        DAY = 'd',
        MONTH = 'm'
    };

    void Initialise(const std::string& symbol) override;

    void PopulateBarsContainer(const std::string& stockData);
};

std::string ConstructUrl(const std::string& symbol,
                         int fromDay,
                         YahooCSVDataProvider::Month fromMonth,
                         int fromYear,
                         int toDay,
                         YahooCSVDataProvider::Month toMonth,
                         int toYear,
                         YahooCSVDataProvider::TradingPeriod);

std::vector<std::string> SeparateCommaSeparatedString(const std::string &line);

#endif // YAHOOCSVDATAPROVIDER_H
