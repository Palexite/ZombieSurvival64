#include "chars_def.h"
#include "utility/data.h"
#include "utility/string_extended.h"

namespace data::characters {
    std::vector<charDef> charsDefined = {};


    void loadCharacters() {

        charDef currentDef = {};

        std::string content = data::readtxt("rom:/data/chars.txt");
        


            for( std::string line : data::getLinesFromString(content)) {
                if (!line.empty() && line.back() == '\r') {
                    line.pop_back();
                }

                // Skip empty lines
                if (line.empty()) {
                    continue;
                }
                

                if(line.starts_with("[")) {
                    currentDef = {};
                } else if(line.starts_with("]")) {

                        charsDefined.push_back(currentDef);

                } else {
                    std::vector<std::string> property = string_ext::Sep(line, " = ");
                    if (property.size() < 2) {
                        continue;
                    }
                const std::string& key = property[0];
                const std::string& value = property[1];
                    
                if(key == "name") {
                    currentDef.name = value;
                } else
                if(key == "desc") {
                    currentDef.desc = value;
                } else
                if(key == "previewasset") {
                    currentDef.previewAsset = value;
                } else
                if(key == "gameasset") {
                    currentDef.gameAsset = value;
                }
            }
            }
    }
}