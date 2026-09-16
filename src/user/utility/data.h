#pragma once

#include <map>
#include <string>

// For interacting with text files. Used for dynamically loading maps and other data.

namespace data {
    std::string readtxt(std::string filePath);
}
