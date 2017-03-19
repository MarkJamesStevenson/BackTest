#include <gtest/gtest.h>
#include "yahoocsvdataprovider.h"

TEST (YahooCSVDataProvider, ConstructUrl) {
    std::string url = ConstructUrl("FDSA.L",
                                   16,
                                   YahooCSVDataProvider::Month::FEBRUARY,
                                   2016,
                                   19,
                                   YahooCSVDataProvider::Month::MARCH,
                                   2016,
                                   YahooCSVDataProvider::TradingPeriod::DAY);
    EXPECT_EQ(url, "http://real-chart.finance.yahoo.com/table.csv?s=FDSA.L&a=1&b=16&c=2016&d=2&e=19&f=2016&g=d&ignore=.csv");
}

TEST (YahooCSVDataProvider, ConstructUrl2) {
    std::string url = ConstructUrl("FDSA.L",
                                   23,
                                   YahooCSVDataProvider::Month::JUNE,
                                   2012,
                                   4,
                                   YahooCSVDataProvider::Month::DECEMBER,
                                   2013,
                                   YahooCSVDataProvider::TradingPeriod::DAY);
    EXPECT_EQ(url, "http://real-chart.finance.yahoo.com/table.csv?s=FDSA.L&a=5&b=23&c=2012&d=11&e=4&f=2013&g=d&ignore=.csv");
}

TEST (YahooCSVDataProvider, ConstructUrlMonthlyPeriod) {
    std::string url = ConstructUrl("FDSA.L",
                                   23,
                                   YahooCSVDataProvider::Month::JUNE,
                                   2012,
                                   4,
                                   YahooCSVDataProvider::Month::DECEMBER,
                                   2013,
                                   YahooCSVDataProvider::TradingPeriod::MONTH);
    EXPECT_EQ(url, "http://real-chart.finance.yahoo.com/table.csv?s=FDSA.L&a=5&b=23&c=2012&d=11&e=4&f=2013&g=m&ignore=.csv");
}
