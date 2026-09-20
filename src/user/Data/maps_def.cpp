#include "maps_def.h"
#include "utility/data.h"
#include "utility/string_extended.h"
#include <cstdio>
namespace data::maps {
std::vector<maps::mapDef> mapsDefined{};

    void loadMaps() {

        mapDef currentDef{};
        


        std::string content = data::readtxt("rom:/data/maps.txt");
        if (content.empty()) {
            currentDef.name = "No maps found";
           mapsDefined.push_back(currentDef);
            return;
        }
        /*
        size_t pos = 0;
        while (pos < content.size()) {
            size_t nextPos = content.find('\n', pos);
            if (nextPos == std::string::npos) {
                nextPos = content.size();
            }

            std::string line = content.substr(pos, nextPos - pos);
            pos = nextPos + 1;
        */
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

                    mapsDefined.push_back(currentDef);

            } else {
                std::vector<std::string> property = string_ext::Sep(line, " = ");
                if (property.size() < 2) {
                    continue;
                }
            const std::string& key = property[0];
            const std::string& value = property[1];

                // variable checks
                if(key == "name") {
                    currentDef.name = value;
                } else if(key == "desc") {
                    currentDef.desc = value;
                } else if(key =="icon") {
                    currentDef.icon = value;
                } else if(key == "creator") {
                    currentDef.originCreator = value;
                } else if(key == "importer") {
                    currentDef.importer = value;
                } else if(key == "difficulty") {
                    currentDef.difficulty = std::stoi(value);
                } else if(key == "size") {
                    currentDef.size = std::stoi(value);
                } else if(key == "category") {
                    currentDef.category = value;
                } else if(key == "date") {
                    currentDef.date = value;
                }
                

            }
            
    }
    }
}