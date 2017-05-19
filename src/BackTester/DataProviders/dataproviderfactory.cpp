#include "dataproviderfactory.h"
#include "yahoocsvdataprovider.h"
#include "yahoocsvfiledataprovider.h"
#include <cassert>
#include <memory>
#include "dataprovider.h"

std::unique_ptr<DataProvider> DataProviderFactory::CreateDataProvider(DataSource provider, std::string symbol)
{
    std::unique_ptr<DataProvider> dataProvider = nullptr;
    switch (provider) {
        case DataSource::YAHOOCSVDATAPROVIDER :
            dataProvider = std::make_unique<YahooCSVDataProvider>();
            break;
        case DataSource::YAHOOCSVFILEDATAPROVIDER :
            dataProvider = std::make_unique<YahooCSVFileDataProvider>();
            break;
        default:
            assert(false && "The data provider hasn't been added to the switch statement");
            break;
    };
    dataProvider->Initialise(symbol);
    return dataProvider;
}
