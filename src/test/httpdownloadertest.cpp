#include <gtest/gtest.h>
#include "httpdownloader.h"


TEST (HTTPDownloader, DISABLED_checkDataConsistency) {
    //This test is currently failing as yahoo finance now requires cookies to download data
    HTTPDownloader downloader;
    std::string url = "https://uk.finance.yahoo.com/quote/MSFT/history?p=MSFT";
    std::string stockData = downloader.Download(url);
    std::cout << stockData;
}
