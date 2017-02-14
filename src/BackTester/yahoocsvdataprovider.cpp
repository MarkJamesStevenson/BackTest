#include "yahoocsvdataprovider.h"
#include "httpdownloader.h"
#include <iostream>
#include "curl/curl.h"
#include <string>
#include <cstdlib>

void YahooCSVDataProvider::Initialise(const std::string &symbol)
{
    std::cout << "Downloading the stock data for " << symbol << std::endl;
    std::string url = ConstructUrl(symbol, 1, 1, 2000, 1, 1, 2017, 'd');
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

std::string YahooCSVDataProvider::ConstructUrl(const std::string& symbol,
                                               int fromMonth,
                                               int fromDay,
                                               int fromYear,
                                               int toMonth,
                                               int toDay,
                                               int toYear,
                                               char tradingPeriod)
{
    std::string url = "http://real-chart.finance.yahoo.com/table.csv?s=" +
    symbol +
    "&a=" + std::to_string(fromMonth - 1) +
    "&b=" + std::to_string(fromDay) +
    "&c=" + std::to_string(fromYear) +
    "&d=" + std::to_string(toMonth - 1) +
    "&e=" + std::to_string(toDay) +
    "&f=" + std::to_string(toYear) +
    "&g=" + tradingPeriod +
    "&ignore=.csv";
    return url;
}
