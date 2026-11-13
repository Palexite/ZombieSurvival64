#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "UI/Popup.h"
#include "UI/gradbutton.h"
#include <vector>
#include <string>
#include "UI/keyboard.h"
#include "UI/xpBar.h"

namespace UI {
class UserMenu {
    public:
    int curSelection = 0;
    int w = 640;
    int h = 480;
    std::vector<GradientButton*> buttons;
    

    Popup* warningPopup = nullptr;
    P64::Object *owner = nullptr;
    Keyboard *keyboard = nullptr;
    UI::XPBar *xpBar = nullptr;
    void Draw(float deltaTime);
    void Update(float deltaTime);
    
    UserMenu(P64::Object* owner);
    ~UserMenu();

    private:
    bool mainInput = true;
};
}