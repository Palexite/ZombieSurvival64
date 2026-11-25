#include "CharSelect.h"

#include "Globals/global.h"
#include "Globals/players.h"
#include "Globals/game.h"

#include "utility/splitscreen.h"

#include <utility>

namespace UI {

    CharSelect::CharSelect(P64::Object& linkedObject, P64::ObjectRef placeholdCamera)
        : linkedObject(linkedObject) {
    this->placeholdCamera = placeholdCamera; 
    for(int i=1; i <= players::portCount; i++) {
      
      uint16_t objId = P64::SceneManager::getCurrent().addObject("prefabs/PreviewCharacter.pf"_asset);
      deferredChars.push_back(objId);
    }

    }

    void CharSelect::update(P64::Object& obj, float deltaTime) {
        for (size_t i = 0; i < this->deferredChars.size(); i++) {
            P64::Object* object = P64::SceneManager::getCurrent().getObjectById(this->deferredChars[i]);
            if (!object) {
                
                continue;
            }
            this->prevChars.emplace_back(
                this->currentPortCount,
                object, 
                splitscreen::calculateDimensions(this->currentPortCount, players::portCount),
                this->placeholdCamera
            );
            auto newChar = std::make_unique<CharSelectCorner>(this->currentPortCount, object);
            this->charSelectCorners.emplace_back(
                newChar.get()
            );
            P64::User::panels.emplace_back(std::move(newChar));

            this->deferredChars.erase(this->deferredChars.begin() + i);
            this->currentPortCount += 1;
        }


        for(UI::previewChar prevChar : this->prevChars) {
            prevChar.Update(deltaTime);
        }

        for(UI::CharSelectCorner *corner : this->charSelectCorners) {
            corner->update(deltaTime);
        }
    }



    void CharSelect::draw(float deltaTime) {
    }
    };
