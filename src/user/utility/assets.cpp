#include <cstring>
#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include "assets.h"
#include <libdragon.h>
#include "../../p64/assetTable.h"
#include "assets/assetManager.h"

// Cache for asset indices to avoid repeated lookups
std::map<std::string, uint32_t> assetIndexCache{};


  // This is needed instead of the native equivalent in AssetTable.h since it does not take dynamic paths.
namespace utility::assets
{
    static std::string normalizeAssetPath(const char *path)
    {
        if (!path) {
            return {};
        }

        std::string normalized(path);
        if (normalized.starts_with("rom:/")) {
            normalized.erase(0, 5);
        }

        while (!normalized.empty() &&
               (normalized.back() == '\r' || normalized.back() == '\n' ||
                normalized.back() == ' ' || normalized.back() == '\t')) {
            normalized.pop_back();
        }

        return normalized;
    }

    uint32_t findAssetIndex(const char *path)
    {
        const std::string lookupPath = normalizeAssetPath(path);
        if (lookupPath.empty()) {
            return UINT32_MAX;
        }

        if(assetIndexCache.contains(lookupPath)) {
            return assetIndexCache[lookupPath];
        } else {


            for (uint32_t index = 0;; ++index) {
                const char *registeredPath = P64::AssetManager::getPathByIndex(index);

                if (!registeredPath) {
                    return UINT32_MAX;
                }

                if (normalizeAssetPath(registeredPath) == lookupPath) {
                    assetIndexCache[lookupPath] = index;
                    return index;
                }
            }
        }
    }
}