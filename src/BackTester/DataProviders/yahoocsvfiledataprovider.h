#ifndef YAHOOCSVFILEDATAPROVIDER_H
#define YAHOOCSVFILEDATAPROVIDER_H

#include "dataprovider.h"
#include <string>
#include <vector>

class YahooCSVFileDataProvider : public DataProvider
{
public:
    YahooCSVFileDataProvider() = default;

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

private:
    void PopulateBars(std::istream &is, const std::string &symbol);
};

#endif // YAHOOCSVFILEDATAPROVIDER_H
