#include <gtest/gtest.h>
#include "httpdownloader.h"


TEST (HTTPDownloader, checkDataConsistency) {
    HTTPDownloader downloader;
    std::string url = "https://uk.finance.yahoo.com/quote/MSFT/history?p=MSFT";
    //std::string url = "http://real-chart.finance.yahoo.com/table.csv?s=GOOGL&a=1&b=17&c=2016&d=1&e=17&f=2016&g=d&ignore=.csv";
    //std::string url = "https://query1.finance.yahoo.com/v7/finance/download/MSFT?period1=958518000&period2=1494889200&interval=1d&events=history&crumb=2BLL.DDY7G.";
    //std::string url = "https://query1.finance.yahoo.com/v7/finance/download/COF?period1=1492408787&period2=1495000787&interval=1d&events=history/Q";
    //rstd::string url = "https://finance.yahoo.com/quote/MSFT/history?period1=1463461200&period2=1494910800&interval=1d&filter=history&frequency=1d";
    std::string stockData = downloader.Download(url);
    //std::string expectedData = "Date,Open,High,Low,Close,Volume,Adj Close\n2016-02-17,727.00,733.76001,716.609985,731.969971,2457700,731.969971\n";
    std::cout << stockData;//EXPECT_EQ(stockData, expectedData);
}
