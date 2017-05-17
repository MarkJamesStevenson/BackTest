#include <gtest/gtest.h>
#include "httpdownloader.h"


TEST (HTTPDownloader, checkDataConsistency) {
    HTTPDownloader downloader;
    std::string url = "http://real-chart.finance.yahoo.com/table.csv?s=GOOGL&a=1&b=17&c=2016&d=1&e=17&f=2016&g=d&ignore=.csv";
    //std::string stockData = downloader.Download(url);
    std::string expectedData = "Date,Open,High,Low,Close,Volume,Adj Close\n2016-02-17,727.00,733.76001,716.609985,731.969971,2457700,731.969971\n";
    //EXPECT_EQ(stockData, expectedData);
}
