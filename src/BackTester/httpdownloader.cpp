#include "httpdownloader.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

HTTPDownloader::HTTPDownloader()
{
    curl = curl_easy_init();
}

HTTPDownloader::~HTTPDownloader()
{
    curl_easy_cleanup(curl);
}

size_t HTTPDownloader::WriteData(const char *ptr, size_t size, size_t nmemb, void *stream) {
    std::string data(ptr, size * nmemb);
    *(static_cast<std::ostringstream*>(stream)) << data;
    return size * nmemb;
}

std::string HTTPDownloader::Download(const std::string &url)
{
    std::ostringstream out;
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, out);
        if (curl_easy_perform(curl) != CURLE_OK) {
            throw std::runtime_error("Unable to download from website");
        }
    }
    else
    {
        throw std::runtime_error("Unable to create cURL object");
    }
    return out.str();
}
