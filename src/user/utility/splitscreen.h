#pragma once


namespace splitscreen {

    struct quadrant {
        float x;
        float y;
        int w;
        int h;
    };

    quadrant CalculateDimensions(int step, int divisions);
}