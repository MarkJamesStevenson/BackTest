#ifndef HTTPDOWNLOADER_H
#define HTTPDOWNLOADER_H

#include "curl/curl.h"
#include <string>


class HTTPDownloader
{
public:
    HTTPDownloader();

    ~HTTPDownloader();

    std::string Download(const std::string& url);

    HTTPDownloader(const HTTPDownloader&) = delete;
    HTTPDownloader& operator=(const HTTPDownloader&) = delete;

private:
    static size_t WriteData(void *ptr, size_t size, size_t nmemb, void *stream);

    CURL* curl;
};

#endif // HTTPDOWNLOADER_H
