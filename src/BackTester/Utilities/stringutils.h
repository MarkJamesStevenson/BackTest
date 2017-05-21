#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>

class QDateTime;

namespace StringUtils
{
    std::vector<std::string> Split(const std::string &line, char delimiter = ',');

    // Converts from YYYY-MM-DD format to a QDateTime
    QDateTime ConvertStringToQDateTimeFormat(const std::string& inputString, char delimiter = '-');
}

#endif // STRINGUTILS_H
