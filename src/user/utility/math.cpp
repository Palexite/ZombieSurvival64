#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "math.h"



namespace Math_Extended {
  fm_quat_t LookAt(fm_vec3_t pos1, fm_vec3_t pos2) {
      float pitch = atan2f(pos2.x - pos1.x, pos2.z - pos1.z);

      fm_quat_t out;
      fm_quat_from_euler_zyx(&out,0, pitch - 3.15, 0);
      return out;
   }
}