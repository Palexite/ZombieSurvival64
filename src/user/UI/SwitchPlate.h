#include "Panel.h"
#include <vector>
#include <string>
#include <functional>

#include "utility/fonts.h"
#include "utility/math.h"
#include "utility/splitscreen.h"


class SwitchPlate : public UI::Panel {

    public:

    quadrant bounds = {0, 0, scrW, scrH/4};
    std::vector<std::string> options = {};
    int select = 0;

    bool active = true;
    std::function<void(int)> onSelect;
    uint16_t fontId = 1;

    uint16_t PortId = 0;
    SwitchPlate(uint16_t fontId, const std::vector<std::string>& options, const std::function<void(int)>& onSelect);
    void update(float deltaTime) override;
    void draw(float deltaTime) override;
    void switchOption(bool direction);

    private:
    bool changingOption;
    float animTime;
    float startTime = 0.5;
    int prevSelect;
};