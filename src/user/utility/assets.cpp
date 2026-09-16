#include <cstring>
#include <cstdint>
#include <map>
#include <string>
#include "assets.h"
#include <libdragon.h>
#include "../../p64/assetTable.h"
#include "assets/assetManager.h"

// Cache for asset indices to avoid repeated lookups
std::map<std::string, uint32_t> assetIndexCache{};


  // This is needed instead of the native equivalent in AssetTable.h since it does not take dynamic paths.
namespace utility::assets
{
    uint32_t findAssetIndex(const char *path)
    {
        if(assetIndexCache.contains(path)) {
            return assetIndexCache[path];
        } else {


            for (uint32_t index = 0;; ++index) {
                const char *registeredPath = P64::AssetManager::getPathByIndex(index);

                if (!registeredPath) {
                    return UINT32_MAX;
                }

                if (std::strcmp(registeredPath, path) == 0) {
                    assetIndexCache[path] = index;
                    return index;
                }
            }
        }
    }
}