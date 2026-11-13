#pragma once

#include "script/userScript.h"
#include "scene/sceneManager.h"
#include <functional>
#include <string>
#include <vector>

class Popup {
    public:

    float x = 0;
    float y = 0;
    int w = 640;
    int h = 480;

    float curTime = 0;
    float EaseInDur = 0.2;

    bool closeRequest = false;
    
    uint8_t curChoice = 0;
    sprite_t *bgSprite = nullptr;
    std::string titleText;
    std::string descText;

    std::string fontName;
    color_t bgColor;
    std::vector<std::string> choices;
    std::function<void(int)> choiceCallback;
    P64::Object *owner = nullptr;

    Popup(float x, float y, int w, int h,

        const std::string& titleText, 
        const std::string& descText, 
        color_t bgColor, 
        std::string fontName, 
        const std::vector<std::string>& choices, 
        std::function<void(int)> choiceCallback, 
        P64::Object *owner);


  ~Popup();
    void draw(float deltaTime);

    void Close();

    void update(float deltaTime);

    private:
    uint16_t fontId;
};