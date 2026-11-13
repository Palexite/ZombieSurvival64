#include "utility/math.h"

namespace UI {

    class XPBar {
        public:
        uint8_t port = 1;
        quadrant bounds; 
        uint8_t screenDiv = 1;

        sprite_t *gradSpr;
        sprite_t *whiteSpr;

        XPBar(uint8_t port, quadrant quad, uint8_t screenSpaceDiv);

        void draw(float deltaTime);
        void update(float deltaTime);

        private:
        uint16_t fontId = 1;
    };

}