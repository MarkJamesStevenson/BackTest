#ifndef YAHOOCSVDATAPROVIDER_H
#define YAHOOCSVDATAPROVIDER_H

#include "dataprovider.h"
#include <string>
#include <vector>
#include <QObject>

class YahooCSVDataProvider : public DataProvider
{
    Q_OBJECT
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

private:
    void PopulateBars(const std::string& stockData);
};

std::string ConstructUrl(const std::string& symbol,
                         int fromDay,
                         YahooCSVDataProvider::Month fromMonth,
                         int fromYear,
                         int toDay,
                         YahooCSVDataProvider::Month toMonth,
                         int toYear,
                         YahooCSVDataProvider::TradingPeriod);

#endif // YAHOOCSVDATAPROVIDER_H
