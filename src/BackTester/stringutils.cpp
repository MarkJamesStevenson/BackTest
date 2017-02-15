#include "stringutils.h"

#include <string>
#include <sstream>
#include <vector>

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
}

