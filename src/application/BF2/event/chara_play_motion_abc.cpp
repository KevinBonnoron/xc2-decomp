#include "event/chara_play_motion_abc.h"

namespace event {

CharaPlayMotionABC::CharaPlayMotionABC() {
  unknown08 = 0;
  unknown10 = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  unknown18 = 0;
  unknown20 = 0;
  unknown28 = 0;
  unknown58 = 0.0f;
  unknown5c = 0.0f;
  unknown60 = 0;
  unknown68 = 0.0f;
  unknown6c = 0.0f;
  unknown70 = 0.0f;
  unknown74 = 0.0f;
  unknown78 = 0.0f;
  unknown7c = 0.0f;
}

bool CharaPlayMotionABC::has(unsigned int index) const { return unknown34[index] > -1; }

} // namespace event
