#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>

extern uint8_t FONTSIZE_MINI;
extern uint8_t FONTSIZE_SMALL;
extern uint8_t FONTSIZE_MEDIUM;
extern uint8_t FONTSIZE_LARGE;

namespace fonts {

    /// @brief A packed list of all the fonts registered for use so they can be referred to by their name and size instead of ID.
    extern std::map<std::string, std::vector<uint8_t>> fontMap;

    /// @brief Register a font given a name, and a series of sizes in the format 0 = MINI, 1 = SMALL, 2 = MED, 3 = LARGE, 4 = XLARGE
    extern void registerFont(std::string fontName, std::vector<uint8_t>);


    /// @brief Retrieves the font by it's name, size, and the division of it's size.
    /// @param fontName the name of the font that is registered.
    /// @param fontSize the size of the font as according to the format 0 = MINI, 1 = SMALL, 2 = MED, 3 = LARGE, 4 = XLARGE.
    /// @param fontDiv the division of the font's size; used for split-screen sizing. (NOTE: this internally acts as an offset of fontSize which decreases it.) Only values 1, 2, and 4 are acceptable.
    extern uint16_t getFont(const std::string& fontName, uint8_t fontSize, uint8_t fontDiv);

    /// @brief Wrapper function that tells the game to just set up a bunch of default fonts from ROM.
    extern void setupFonts();
}