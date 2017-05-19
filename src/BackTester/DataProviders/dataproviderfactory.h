#ifndef DATAPROVIDERFACTORY_H
#define DATAPROVIDERFACTORY_H

#include <string>
#include <memory>
#include "dataprovider.h"

enum class DataSource {
    YAHOOCSVDATAPROVIDER,
    YAHOOCSVFILEDATAPROVIDER
};

class DataProviderFactory
{
public:
    DataProviderFactory() = default;

    std::unique_ptr<DataProvider> CreateDataProvider(DataSource provider, std::string symbol);

    DataProviderFactory(const DataProvider&) = delete;
    DataProviderFactory& operator=(const DataProviderFactory&) = delete;
};

#endif // DATAPROVIDERFACTORY_H
