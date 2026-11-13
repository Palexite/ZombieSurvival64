#include "script/userScript.h"
#include "scene/sceneManager.h"
#include <functional>
#include <string>
#include <vector>
#include "utility/math.h"
#include "gradbutton.h"

namespace UI {
class Keyboard {
    public:

    quadrant quad{100, 200, 480, 480};

    std::string inputText;

    std::string fontname;

    int select = 0;

    uint32_t maxChars = 16;

    const char* title;

    const char* validChars;

    std::vector<GradientButton> buttons;

    std::function<void(std::string)> onEnterCallback;

    Keyboard(const char* title, std::string fontName, std::string defaultInput, uint32_t maxChars);

    void draw(float deltaTime);
    void update(float deltaTime);
    
    private:
    int16_t fontId;
    float animRatio = 0;
    float animTime = 0.25;
    float animDelta = 0;
    float cursorRotation = 0;

    uint8_t rowSize = 12;
};
}
