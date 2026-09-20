#include <string>
#include <vector>

namespace data::characters {
    struct charDef {
    std::string name;
    std::string desc;
    std::string model_main;
    std::string model_head;
    std::string model_hands;
    std::string tex_main;
    std::string tex_head;
    std::string tex_hands;

    std::string prevanim_idle;
    };
    extern std::vector<charDef> charsDefined;
    void loadCharacters();
}