#pragma once

#include <map>
#include <string>
#include <list>
#include <vector>
namespace maps {
    struct mapDef {
    std::string name;
    std::string originCreator;
    std::string importer;
    std::string desc;
    std::string icon;
        int scene = 1;
        int difficulty = 1;
        int size = 1;
        bool isObjective = false;
        
    };
    void loadMaps();

    extern std::vector<maps::mapDef> mapsDefined;

}
