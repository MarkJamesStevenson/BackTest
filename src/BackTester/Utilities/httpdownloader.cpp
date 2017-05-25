#include "httpdownloader.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

HTTPDownloader::HTTPDownloader()
{
    curl = curl_easy_init();
    if (curl == nullptr)
    {
        throw std::runtime_error("Unable to create cURL object");
    }
}

HTTPDownloader::~HTTPDownloader()
{
    curl_easy_cleanup(curl);
}

size_t HTTPDownloader::WriteData(const char *ptr, size_t size, size_t nmemb, void *stream)
{
    std::string data(ptr, size * nmemb);
    *(static_cast<std::ostringstream*>(stream)) << data;
    std::cout << stream << std::endl;
    return size * nmemb;
}

std::string HTTPDownloader::Download(const std::string &url)
{
    std::ostringstream out;
    if (curl)
    {
        //curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
        curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1L);
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./testcookie");
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./testcookie");
        //if (curl_easy_perform(curl) != CURLE_OK) {
        //    throw std::runtime_error("Unable to download from website");
        //}
        std::string newUrl = "https://query1.finance.yahoo.com/v7/finance/download/MSFT?period1=958518000&period2=1494889200&interval=1d&events=history";
        curl_easy_setopt(curl, CURLOPT_URL, newUrl.c_str());
        if (curl_easy_perform(curl) != CURLE_OK) {
            throw std::runtime_error("Unable to download from website");
        }
    }
    return out.str();
}
