#include "string_extended.h"


namespace string_ext {
std::vector<std::string> Sep(const std::string& input, const std::string& delimiter) {

        std::vector<std::string> tokens;
    if (delimiter.empty()) {
        tokens.push_back(input);
        return tokens;
    }
    size_t start = 0;
    size_t end;

        while ((end = input.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(input.substr(start, end - start));
        start = end + delimiter.length();
    }
        tokens.push_back(input.substr(start));
    return tokens;
}
}