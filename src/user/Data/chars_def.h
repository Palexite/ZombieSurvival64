#pragma once

#include <string>
#include <vector>

namespace data::characters {
    struct charDef {
    std::string name;
    std::string desc;
    std::string previewAsset;
    std::string gameAsset;
    };
    extern std::vector<charDef> charsDefined;
    void loadCharacters();
}