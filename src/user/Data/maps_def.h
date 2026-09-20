#pragma once

#include <map>
#include <string>
#include <list>
#include <vector>
namespace data::maps {
    struct mapDef {
    std::string name;
    std::string originCreator;
        std::string date;
    std::string importer;
    std::string desc;
    std::string icon;
    std::string category;
        int scene = 1;
        int difficulty = 1;
        int size = 1;
        
    };
    void loadMaps();

    extern std::vector<data::maps::mapDef> mapsDefined;

}
