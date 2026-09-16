#include "maps_def.h"
#include "utility/data.h"
#include "utility/string_extended.h"
#include <cstdio>
namespace maps {
std::vector<maps::mapDef> mapsDefined{};

    void loadMaps() {

        maps::mapDef currentDef{};
        


        std::string content = data::readtxt("rom:/data/maps.txt");
        if (content.empty()) {
            currentDef.name = "No maps found";
            maps::mapsDefined.push_back(currentDef);
            return;
        }


        size_t pos = 0;
        while (pos < content.size()) {
            size_t nextPos = content.find('\n', pos);
            if (nextPos == std::string::npos) {
                nextPos = content.size();
            }

            std::string line = content.substr(pos, nextPos - pos);
            pos = nextPos + 1;

            // Skip empty lines
            if (line.empty()) {
                continue;
            }
            

            if(line.starts_with("[")) {
                currentDef = {};
            } else if(line.starts_with("]")) {

                    maps::mapsDefined.push_back(currentDef);

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
                } else if(key == "isobj") {

                    if(value == "true" || value == "yes" || value == "1")
                        currentDef.isObjective = true;
                    else
                        currentDef.isObjective = false;
                }
                

            }



            /*
            // Parse the line into a mapDef structure
            maps::mapDef map;
            size_t fieldPos = 0;
            size_t fieldEnd;

            // Name
            fieldEnd = line.find(',', fieldPos);
            map.name = line.substr(fieldPos, fieldEnd - fieldPos).c_str();
            fieldPos = fieldEnd + 1;

            // Origin Creator
            fieldEnd = line.find(',', fieldPos);
            map.originCreator = line.substr(fieldPos, fieldEnd - fieldPos).c_str();
            fieldPos = fieldEnd + 1;

            // Importer
            fieldEnd = line.find(',', fieldPos);
            map.importer = line.substr(fieldPos, fieldEnd - fieldPos).c_str();
            fieldPos = fieldEnd + 1;

            // Description
            fieldEnd = line.find(',', fieldPos);
            map.desc = line.substr(fieldPos, fieldEnd - fieldPos).c_str();
            fieldPos = fieldEnd + 1;

            // Icon
            fieldEnd = line.find(',', fieldPos);
            map.icon = line.substr(fieldPos, fieldEnd - fieldPos).c_str();
            fieldPos = fieldEnd + 1;
            */
            
    }
    }
}