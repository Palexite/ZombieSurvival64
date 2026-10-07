#include "CharSelect.h"

#include "Globals/players.h"
#include "Globals/gameplay.h"
#include "utility/splitscreen.h"

namespace UI {

    CharSelect::CharSelect(P64::Object& linkedObject, P64::ObjectRef placeholdCamera)
        : linkedObject(linkedObject) {
    //Creating the previewCharacter objects
    this->placeholdCamera = placeholdCamera; 
    for(int i=1; i <= players::portCount; i++) {
      
      uint16_t objId = P64::SceneManager::getCurrent().addObject("PreviewCharacter.pf"_asset);
      deferredChars.push_back(objId);
      //data->deferredChars.push_back(objId);
    }

    }

    void CharSelect::update(P64::Object& obj, float deltaTime) {
        for (size_t i = 0; i < this->deferredChars.size();) {
            P64::Object* object = P64::SceneManager::getCurrent().getObjectById(this->deferredChars[i]);
            if (!object) {
                ++i;
                continue;
            }
            this->prevChars.emplace_back(
                this->currentPortCount,
                object,
                splitscreen::CalculateDimensions(this->currentPortCount, players::portCount),
                this->placeholdCamera
            );

            this->deferredChars.erase(this->deferredChars.begin() + i);
            this->currentPortCount += 1;
        }
                    for(UI::previewChar prevChar : this->prevChars) {
                prevChar.Update(deltaTime);
            }
    }

    void CharSelect::draw(float deltaTime) {

    }
    };
