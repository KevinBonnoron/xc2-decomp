#include "event/chara_play_motion.h"

namespace event {

CharaPlayMotion::CharaPlayMotion() {
  unknown08 = 0;
  unknown10 = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  unknown18 = 0;
  unknown20 = 0;
  unknown28 = 0;
  unknown30 = 0;
  unknown3c = 0.0f;
  unknown40 = 0.0f;
}

} // namespace event
