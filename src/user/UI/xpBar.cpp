#include "xpBar.h"
#include "utility/controllerpak.h"
#include "utility/fonts.h"
#include "utility/eeprom.h"
#include "utility/splitscreen.h"
#include <inttypes.h>

namespace UI {

    XPBar::XPBar(uint8_t port, quadrant bounds, uint8_t screenDiv) : port(port), bounds(bounds), screenDiv(screenDiv) {

        this->fontId = fonts::getFont(EEPROM_GAME::CurUserSettings.gameFont, 0, screenDiv);

        this->whiteSpr = (sprite_t*)P64::AssetManager::getByIndex("tex/white.sprite"_asset);
        this->gradSpr = (sprite_t*)P64::AssetManager::getByIndex("tex/grad1.sprite"_asset);

        quadrant absQuad = splitscreen::calculateDimensions(port, screenDiv);

        // recalculation based on splitscreen
        bounds = splitscreen::fitQuadToBounds(bounds, absQuad);

 
    }

    void XPBar::draw(float deltaTime) {

        PlayerData pData = controllerpak::CachedPlayerData[port-1];

        uint32_t requiredXP = controllerpak::getRequiredXPToLevel(pData.level);
        float progress = requiredXP == 0
            ? 0.0f
            : static_cast<float>(pData.xp) / static_cast<float>(requiredXP);
        if(progress > 1.0f) {
            progress = 1.0f;
        }

        rdpq_textparms_t TEXT_INDICATOR{
        .width = 320,
        .align = ALIGN_CENTER,
        .disable_aa_fix = false
        };

        rdpq_blitparms_t bgParms{};
        bgParms.scale_x = bounds.w;
        bgParms.scale_y = bounds.h;
        rdpq_blitparms_t progressBarParms{};
        progressBarParms.scale_x = (progress * bounds.w) / 128.0f;
        progressBarParms.scale_y = bounds.h;

        rdpq_set_prim_color(RGBA32(0, 0, 0, 160));
        rdpq_sprite_blit(whiteSpr, bounds.x, bounds.y, &bgParms);
        rdpq_set_prim_color(RGBA32(64, 192, 96, 255));
        rdpq_sprite_blit(gradSpr, bounds.x, bounds.y, &progressBarParms);
        rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
        rdpq_text_printf(&TEXT_INDICATOR, fontId, bounds.x, bounds.y, "Lvl %d // R.Lvl %" PRIu64, pData.level, pData.remortLevel);

    }

}