#pragma once

#include <cstring>
#include <cstdint>
#include <map>
#include <string>

extern std::map<std::string, uint32_t> assetIndexCache;

namespace utility::assets
{
uint32_t findAssetIndex(const char *path);
}