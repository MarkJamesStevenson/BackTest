#ifndef DATAPROVIDERFACTORY_H
#define DATAPROVIDERFACTORY_H

#include <string>
#include <memory>
#include "dataprovider.h"

class DataProviderFactory
{
public:
    enum class DataSource {
        YAHOOCSVDATAPROVIDER
    };

    DataProviderFactory() = default;

    std::unique_ptr<DataProvider> GetDataProvider(DataSource provider, std::string symbol);

    DataProviderFactory(const DataProvider&) = delete;
    DataProviderFactory& operator=(const DataProviderFactory&) = delete;
};

#endif // DATAPROVIDERFACTORY_H
