#include "previewChar.h"
#include "scene/components/Camera.h"


namespace UI {

    previewChar::previewChar(std::int8_t portId, P64::Object *linkedObject, splitscreen::quadrant window, P64::ObjectRef CamToDestroy)
        : charBody(nullptr)
        , linkedObject(linkedObject)
        , portId(portId)
        , window(window)
        , CamToDestroy(CamToDestroy)
    {
        this->Camera = nullptr;
        fm_quat_t customRot = fm_quat_t{1, 0, 0, 0};
        fm_quat_from_euler_zyx(&customRot, 0, 45, 0);
        this->CameraId = P64::SceneManager::getCurrent().addObject("prefabs/Camera.pf"_asset, fm_vec3_t{0, 100, 160}, fm_vec3_t{1, 1, 1});
    }

    void previewChar::changeCharacter(int charId) {
    

    }

    void previewChar::Update(float delta) {
        if(!camInitialized) {
            this->Camera = P64::SceneManager::getCurrent().getObjectById(this->CameraId);

            if(!this->Camera) {
                return;
            }
            P64::Comp::Camera* camComp = Camera->getComponent<P64::Comp::Camera>();

            camComp->camera.setScreenArea(window.x, window.y, window.w, window.h);
            if(window.h == 240 && window.w == 640) {
                camComp->camera.aspectRatio = 2;
            }

            if (P64::Object* placeholderCamera = CamToDestroy.get()) {
                placeholderCamera->setEnabled(false);
                debugf("Preview camera initialized; placeholder disabled\n");
            } else {
                debugf("Preview camera initialized, but placeholder camera is missing\n");
            }
            camInitialized = true;
        }


        fm_vec3_t axis = fm_vec3_t{0, 1, 0};
            fm_quat_rotate(&this->linkedObject->rot, &this->linkedObject->rot, &axis, 0.5 * delta);
    }

    void previewChar::Draw(float deltaTime) {
        
    }

}