#ifndef YAHOOCSVDATAPROVIDER_H
#define YAHOOCSVDATAPROVIDER_H

#include "dataprovider.h"
#include <string>
#include "curl/curl.h"

class YahooCSVDataProvider : public DataProvider
{
public:
    YahooCSVDataProvider() = default;

    bool UrlParser(const std::string& ID, const int& fromMonth, const int& fromDay, const int& fromYear, const int& toMonth, const int& toDay, const int& toYear, char tradingPeriod);

    void DownloadData() override;

    void UpdateBars() override;

private:
    CURL *curl;
    CURLcode result;
};

size_t my_write_func(void *ptr, size_t size, size_t nmemb, FILE *stream);

#endif // YAHOOCSVDATAPROVIDER_H
