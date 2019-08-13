//
// Created by kalos on 13/08/19.
//

#include <cstdlib>
#include <string>

static std::pair<std::string, int64_t> convertInMilliseconds(const std::pair<std::string, int64_t>& pair) {

    if(pair.first == "seconds")
        return std::make_pair("seconds", pair.second*1000);

    if(pair.first == "minutes")
        return std::make_pair("minutes", pair.second*60*1000);

    if(pair.first == "hours")
        return std::make_pair("seconds", pair.second*60*60*1000);

    if(pair.first == "none")
        return pair;
}