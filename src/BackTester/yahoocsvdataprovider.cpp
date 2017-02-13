#include "yahoocsvdataprovider.h"
#include <iostream>
#include "curl/curl.h"
#include <string>

using namespace std;

void YahooCSVDataProvider::DownloadData()
{
    std::cout << "Downloading the data to disk" << std::endl;
    UrlParser("hi", 1, 2, 3, 4, 5, 6, 'A');
}

void YahooCSVDataProvider::UpdateBars()
{

}
size_t my_write_func(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return fwrite(ptr, size, nmemb, stream);
}

bool YahooCSVDataProvider::UrlParser(const string& ID, const int& fromMonth, const int& fromDay, const int& fromYear, const int& toMonth, const int& toDay, const int& toYear, char tradingPeriod)
{
    curl = curl_easy_init();
    if (curl) {
        FILE* my_file;
        errno_t err;
        const char* file_name = "archive\\test.txt";

        if ((err = fopen_s(&my_file, file_name, "w")) != 0)
        {
            perror("Error opening file");
            return false;
        }
        else
        {
            curl_easy_setopt(curl, CURLOPT_URL, "http://real-chart.finance.yahoo.com/table.csv?s=VOD.L&a=0&b=1&c=2016&d=4&e=9&f=2016&g=d&ignore=.csv");

            //send the data to the memory function
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write_func);

            //pass chunk struct to the callback function
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, my_file);

            result = curl_easy_perform(curl);

            /* always cleanup */
            curl_easy_cleanup(curl);

            if (result == CURLE_OK)
            {
                std::cout << "Successfully parsed data to " << std::endl;
            }
            else
            {
                std::cout << "Error parsing data." << result << std::endl;
                return false;
            }
        }
    }
    return true;
}
