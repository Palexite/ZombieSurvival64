#include "CharSelectCorner.h"
namespace UI {
    void drawCharSelect();
    CharSelectCorner::CharSelectCorner(float x, float y, float w, float h, int portId) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->portId = portId;
    }
  CharSelectCorner::~CharSelectCorner() = default;



  void CharSelectCorner::Draw() {
    
  }
}