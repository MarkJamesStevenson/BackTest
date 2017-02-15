#include "yahoocsvdataprovider.h"
#include "httpdownloader.h"
#include <iostream>
#include "curl/curl.h"
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "ohlcdatapoint.h"

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
    PopulateBarsContainer(stockData);
}

void YahooCSVDataProvider::PopulateBarsContainer(const std::string &stockData)
{
    std::stringstream stream(stockData);
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
            std::vector<std::string> data = SeparateCommaSeparatedString(line);
            std::string date = data[0];
            int open = std::stoi(data[1]);
            int high = std::stoi(data[2]);
            int low = std::stoi(data[3]);
            int close = std::stoi(data[4]);
            int volume = std::stoi(data[5]);
            int adjClose = std::stoi(data[6]);
            bars.emplace_back(OHLCDataPoint(date, open, high, low, close, volume, adjClose));
        }
    }
}

std::vector<std::string> SeparateCommaSeparatedString(const std::string& line)
{
    std::stringstream stream(line);
    std::string token;
    std::vector<std::string> dataPoints;
    while (std::getline(stream, token, ','))
    {
        dataPoints.push_back(token);
    }
    return dataPoints;
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
