#include "yahoocsvfiledataprovider.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "stringutils.h"
#include <exception>
#include <cassert>
#include "marketevent.h"

void YahooCSVFileDataProvider::Initialise(const std::string &directory)
{
    std::cout << "Trying to find data file: " << directory << "\n";
    std::ifstream inputFile(directory);
    if(inputFile)
    {
        std::cout << "Data file found\n";
        //TODO: Rename the stock to not be the directory
        PopulateBars(inputFile, directory);
    }
    else
    {
        std::string error = "Could not open file: " + directory;
        throw std::runtime_error(error);
    }
}

void YahooCSVFileDataProvider::UpdateBars()
{
    assert(DataAvailable() && "Should not call without checking it has data");
    emit PublishMarketEvent(MarketEvent(bars.front()));
    bars.pop();
}

bool YahooCSVFileDataProvider::DataAvailable() const
{
    return !bars.empty();
}

void YahooCSVFileDataProvider::PopulateBars(std::istream& is, const std::string& symbol)
{

    bool header = true;
    std::string line;
    while(std::getline(is, line))
    {
        if (header)
        {
            // We want to ignore the first line as it is a header
            header = false;
        }
        else
        {
            std::vector<std::string> data = StringUtils::Split(line);
            if (data.size() != 7)
            {
                throw std::range_error(std::string("Vector should be of size 7. Received: " + std::to_string(data.size())));
            }
            QDateTime date = StringUtils::ConvertStringToQDateTimeFormat(data[0]);
            double open = std::stod(data[1]);
            double high = std::stod(data[2]);
            double low = std::stod(data[3]);
            double close = std::stod(data[4]);
            double adjClose = std::stod(data[6]);
            double volume = std::stod(data[5]);
            bars.push(OHLCDataPoint(symbol, date, open, high, low, close, adjClose, volume));
        }
    }
}
