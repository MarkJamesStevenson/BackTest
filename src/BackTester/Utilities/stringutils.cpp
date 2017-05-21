#include "stringutils.h"

#include <string>
#include <sstream>
#include <vector>
#include <QDateTime>
#include <iostream>

namespace StringUtils
{
    std::vector<std::string> Split(const std::string& line, char delimiter)
    {
        std::istringstream stream(line);
        std::string token;
        std::vector<std::string> separated;
        while (std::getline(stream, token, delimiter))
        {
            separated.push_back(token);
        }
        return separated;
    }

    QDateTime ConvertStringToQDateTimeFormat(const std::string& inputString, char delimiter)
    {
        std::istringstream stream(inputString);
        std::string token;
        std::vector<std::string> separated;
        while (std::getline(stream, token, delimiter))
        {
            separated.push_back(token);
        }
        if (separated.size() == 3)
        {
            int year = stoi(separated[0]);
            int month = stoi(separated[1]);
            int day = stoi(separated[2]);
            return QDateTime(QDate(year, month, day));
        }
        else
        {
            throw std::runtime_error(std::string("Input date was not of the expected form DD-MM-YYYY: " + inputString));
        }
    }
}

