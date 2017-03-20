#include "yahoocsvdataprovider.h"
#include "httpdownloader.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "ohlcdatapoint.h"
#include "stringutils.h"
#include <exception>

void YahooCSVDataProvider::Initialise(const std::string &symbol)
{
    std::cout << "Downloading the stock data for " << symbol << std::endl;
    const std::string url = ConstructUrl(symbol,
                                         1, Month::JANUARY, 2000,
                                         1, Month::JANUARY, 2017,
                                         TradingPeriod::DAY);
    HTTPDownloader downloader;
    std::string stockData = downloader.Download(url);
    PopulateBars(symbol, stockData);
}

void YahooCSVDataProvider::PopulateBars(const std::string& symbol, const std::string &stockData)
{
    std::istringstream stream(stockData);
    std::string line;
    bool header = true;
    while (std::getline(stream, line))
    {
        if (header)
        {
            // We want to ignore the first line as it is a header
            header = false;
        }
        else
        {
            const std::vector<std::string> data = StringUtils::Split(line);
            if (data.size() != 7)
            {
                throw std::range_error(std::string("Vector should be of size 7. Received: " + std::to_string(data.size())));
            }
            const std::string date = data[0];
            double open = std::stod(data[1]);
            double high = std::stod(data[2]);
            double low = std::stod(data[3]);
            double close = std::stod(data[4]);
            double volume = std::stod(data[5]);
            double adjClose = std::stod(data[6]);
            bars.emplace_back(symbol, date, open, high, low, close, volume, adjClose);
        }
    }
}

std::string ConstructUrl(const std::string& symbol,
                         int fromDay,
                         YahooCSVDataProvider::Month fromMonth,
                         int fromYear,
                         int toDay,
                         YahooCSVDataProvider::Month toMonth,
                         int toYear,
                         YahooCSVDataProvider::TradingPeriod tradingPeriod)
{
    return "http://real-chart.finance.yahoo.com/table.csv?s=" +
    symbol +
    "&a=" + std::to_string(static_cast<int>(fromMonth)) +
    "&b=" + std::to_string(fromDay) +
    "&c=" + std::to_string(fromYear) +
    "&d=" + std::to_string(static_cast<int>(toMonth)) +
    "&e=" + std::to_string(toDay) +
    "&f=" + std::to_string(toYear) +
    "&g=" + static_cast<char>(tradingPeriod) +
    "&ignore=.csv";
}
