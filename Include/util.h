#ifndef _UTIL_H
#define _UTIL_H

#include <algorithm>
#include <iterator>
#include <string>

inline std::string string_to_upper(std::string str) {
    std::string &temp = str;
    std::for_each(std::begin(temp), std::end(temp), [](char& c) {
        /* from the docs the, argument to toupper should be representable as
            unsigned char or EOF or else it's UB
         */
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    });
    return temp;
}

#endif