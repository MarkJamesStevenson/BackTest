#ifndef YAHOOCSVFILEDATAPROVIDER_H
#define YAHOOCSVFILEDATAPROVIDER_H

#include "dataprovider.h"
#include <string>
#include <queue>

class YahooCSVFileDataProvider : public DataProvider
{
public:
    YahooCSVFileDataProvider() = default;

    void Initialise(const std::string& symbol) override;

    void UpdateBars() override;

    bool DataAvailable() const override;

private:
    void PopulateBars(std::istream &is, const std::string &symbol);

    std::queue<OHLCDataPoint> bars;
};

#endif // YAHOOCSVFILEDATAPROVIDER_H
