#include "fonts.h"
#include <algorithm>
#include "libdragon.h"


uint8_t FONTSIZE_MINI = 0;
uint8_t FONTSIZE_SMALL = 1;
uint8_t FONTSIZE_MEDIUM = 2;
uint8_t FONTSIZE_LARGE = 3;

namespace fonts {

    std::map<std::string, std::vector<uint8_t>> fontMap{};

    void registerFont(std::string fontName, std::vector<uint8_t> fontId) {
        fontMap[fontName] = fontId;
        //fontMap.emplace(fontMap.end(), fontName, fontId);
    }

    
    void setupFonts() {

        rdpq_font_t *font = rdpq_font_load("rom:/fonts/RemingtonNoiseless_Large.font64");

        // Setting up styles for all text
        rdpq_fontstyle_t normal = {};
        normal.color = RGBA16(31, 31, 31, 1);

        rdpq_fontstyle_t outlineStyle = {};
        outlineStyle.color = RGBA16(0, 0, 0, 1);

        rdpq_fontstyle_t Locked = {};
        Locked.color = RGBA32(255, 255, 255, 125);

        rdpq_font_style(font, 0, &normal);
        rdpq_font_style(font, 1, &outlineStyle);
        rdpq_text_register_font(4, font);


        font = rdpq_font_load("rom:/fonts/RemingtonNoiseless_Med.font64");
        rdpq_font_style(font, 0, &normal);
            rdpq_font_style(font, 1, &outlineStyle);
        rdpq_text_register_font(3, font);


            font = rdpq_font_load("rom:/fonts/RemingtonNoiseless_Small.font64");
        rdpq_font_style(font, 0, &normal);
        rdpq_font_style(font, 1, &outlineStyle);
        rdpq_font_style(font, 2, &Locked);
        
        rdpq_text_register_font(2, font);


            font = rdpq_font_load("rom:/fonts/RemingtonNoiseless_Mini.font64");
        rdpq_font_style(font, 0, &normal);
        rdpq_font_style(font, 1, &outlineStyle);
        rdpq_font_style(font, 2, &Locked);
        rdpq_text_register_font(1, font);

    std::vector<uint8_t> fontsBySize{
        1,
        2,
        3,
        4
    };

    registerFont("remingtonnoiseless", fontsBySize);


    }

     uint16_t getFont(const std::string& fontName, uint8_t fontSize, uint8_t fontDiv) {
        std::vector<uint8_t> fontIds = fontMap[fontName];


        // The offset relies on the assumption that the fonts before chosen FontID are divisions by two. This is how split screen sizes work consistently but without a hundred different fonts.
        uint8_t offset = 0;

        switch (fontDiv) {

            case 1:
                offset = 0;
                break;
            case 2:
                offset = 1;
                break;

            case 3:
                offset = 2;
                break;

            case 4:
                offset = 2;
                break;

        }
        return fontIds[std::clamp<uint8_t>((fontSize) - offset, 0, 255)];

    };

}
