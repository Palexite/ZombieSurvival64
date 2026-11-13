#include "libdragon.h"
#include "utility/math.h"
namespace UI {

    class ColorPicker {
        public:
        
        color_t chosenColor = RGBA32(255, 255, 255, 255);
        
        ColorPicker();

        void update(float deltaTime);

        void draw(float deltaTime);


    };


}