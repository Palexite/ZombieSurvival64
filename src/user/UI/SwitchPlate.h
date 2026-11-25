#include "Panel.h"
#include <vector>
#include <string>
#include <functional>

#include "utility/fonts.h"
#include "utility/math.h"
#include "utility/splitscreen.h"

namespace UI {
class SwitchPlate : public UI::Panel {

    public:

    quadrant bounds = {0, 0, scrW, scrH/4};
    std::vector<std::string> options = {};
    int select = 0;

    std::function<void(int)> onSelect;
    uint16_t fontId = 1;

    float padding = 64;

    uint16_t portId = 0;
    SwitchPlate(quadrant bounds, uint16_t fontId, const std::vector<std::string>& options, const std::function<void(int)>& onSelect, float padding);
    void update(float deltaTime) override;
    void draw(float deltaTime) override;
    void switchOption(bool direction);

    private:
    bool changingOption = false;
    float animTime = 1;
    float animDelta = 0;
    int prevSelect = 0;
};
}