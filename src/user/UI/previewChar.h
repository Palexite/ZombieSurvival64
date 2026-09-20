#include "scene/components/animModel.h"
#include "script/userScript.h"
#include "scene/sceneManager.h"

namespace Comp {
    class AnimModel;
}

namespace UI {
    class previewChar {
        public:
        Comp::AnimModel* charBody = nullptr;
        P64::Object linkedObject;
        int portId = 0;
        void changeCharacter(int charId);
        previewChar(int portId, P64::Object linkedObject);
    };
    
}