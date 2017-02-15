#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>

namespace StringUtils
{
    std::vector<std::string> Split(const std::string &line, char delimiter = ' ');
}

#endif // STRINGUTILS_H
