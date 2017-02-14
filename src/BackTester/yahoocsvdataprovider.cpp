#include "yahoocsvdataprovider.h"
#include "httpdownloader.h"
#include <iostream>
#include "curl/curl.h"
#include <string>
#include <cstdlib>

void YahooCSVDataProvider::Initialise(const std::string &symbol)
{
    std::cout << "Downloading the stock data for " << symbol << std::endl;
    const std::string url = ConstructUrl(symbol,
                                         1,
                                         Month::JANUARY,
                                         2000,
                                         1,
                                         Month::JANUARY,
                                         2017,
                                         TradingPeriod::DAY);
    HTTPDownloader downloader;
    std::string stockData;
    try {
        stockData = downloader.Download(url);
    } catch (const std::exception& e) {
        std::cout << "Unable to continue as could not download stock data \n"
                  << e.what();
        exit(EXIT_FAILURE);
    }
    std::cout << stockData;
}

void YahooCSVDataProvider::UpdateBars()
{

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
    const std::string url = "http://real-chart.finance.yahoo.com/table.csv?s=" +
    symbol +
    "&a=" + std::to_string(static_cast<int>(fromMonth)) +
    "&b=" + std::to_string(fromDay) +
    "&c=" + std::to_string(fromYear) +
    "&d=" + std::to_string(static_cast<int>(toMonth)) +
    "&e=" + std::to_string(toDay) +
    "&f=" + std::to_string(toYear) +
    "&g=" + static_cast<char>(tradingPeriod) +
    "&ignore=.csv";
    return url;
}
