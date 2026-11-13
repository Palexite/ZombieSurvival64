#include "style.h"


namespace UI::Gradient {
    extern void DrawMiddleGradient(int x, int y, int fill, int width, int height, color_t color) {
        sprite_t *fillSpr = (sprite_t*)P64::AssetManager::getByIndex("tex/white.sprite"_asset);
        sprite_t *gradSpr = (sprite_t*)P64::AssetManager::getByIndex("tex/grad1.sprite"_asset);

        const int gradientWidth = (width - fill) / 2;

        rdpq_blitparms_s grad_LSide = {};
        grad_LSide.scale_x = gradientWidth / 128.0f;
        grad_LSide.scale_y = height;
        grad_LSide.flip_x = true;

        rdpq_blitparms_s grad_RSide = {};
        grad_RSide.scale_x = gradientWidth / 128.0f;
        grad_RSide.scale_y = height;

        rdpq_blitparms_s grad_fill = {};
        grad_fill.scale_x = fill;
        grad_fill.scale_y = height;

        const int fillX = x - fill / 2;
        rdpq_set_prim_color(color);
        rdpq_sprite_blit(gradSpr, x - width / 2, y, &grad_LSide);
        rdpq_sprite_blit(fillSpr, fillX, y, &grad_fill);
        rdpq_sprite_blit(gradSpr, fillX + fill, y, &grad_RSide);
    }
}