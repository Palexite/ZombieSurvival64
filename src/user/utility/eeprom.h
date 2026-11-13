#include <stdint.h>
#include <string>

struct UserSettings {
    bool noSound;
    std::string gameFont;
    std::string HMusic;
    std::string ZMusic;
};

namespace EEPROM_GAME {
    extern UserSettings CurUserSettings;
}