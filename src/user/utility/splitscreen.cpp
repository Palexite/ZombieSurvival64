#include "splitscreen.h"

namespace splitscreen {

    uint8_t curScreenDivisions = 1;


    quadrant calculateDimensions(int step, int screens) {

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
            y = h;
        }

        return quadrant{x, y, w ,h};

    };

    ///@brief Fits the quad to a given quad. This is used to rescale UI elements to
    // parts of the UI.
    ///@param relativeQuad the quad that will be fitted
    ///@param bounds the quad that will be used to fit the relativeQuad to it.
    quadrant fitQuadToBounds(quadrant relativeQuad, quadrant bounds) {

        quadrant newQuad{};
        newQuad.w = (relativeQuad.w / scrW) * bounds.w;
        newQuad.h = (relativeQuad.h / scrH) * bounds.h;
        newQuad.x = ((relativeQuad.x / scrW) * bounds.w) + bounds.x;
        newQuad.x = ((relativeQuad.y / scrH) * bounds.h) + bounds.y;
        return newQuad;
    }
}