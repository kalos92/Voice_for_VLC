//
// Created by kalos on 09/05/19.
//
#include "TextOperation.h"

std::string TextOperation::convert_space(std::basic_string<char> &basicString) {

    std::string toReplace("%20");

    size_t pos = basicString.find(toReplace);

    while( pos != std::string::npos) {
        basicString.replace(pos, toReplace.length(), "_");
        pos = basicString.find(toReplace);
    }

    return basicString;
}


void TextOperation::vfv_toupper(std::string *string)
{
       std::transform(string->begin(), string->end(), string->begin(), ::toupper);
}
