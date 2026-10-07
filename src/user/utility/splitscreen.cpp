#include "splitscreen.h"
namespace splitscreen {
    quadrant CalculateDimensions(int step, int screens) {

        int w = 640;
        int h = 480;
        float x = 0;
        float y = 0;

        if(screens == 2) {
            h /= 2;
        }
            
        if(screens == 3 || screens == 4) {
            w /= 2;
            h /= 2;
        }

        if(step == 1 ) {
            x = 0;
            y = 0;
        } else if(step == 2 && screens == 2) {
            y = h;
        } else if(step == 2) {
            x = w;
        } else if(step == 3) {
            x = 0;
            y = h;
        } else if(step == 4) {
            x = w;
            h = h;
        }

        return quadrant{x, y, w ,h};

    }
}