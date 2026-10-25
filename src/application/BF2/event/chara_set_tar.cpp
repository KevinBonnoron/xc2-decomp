#include "event/chara_set_tar.h"

namespace event {

void CharaSetTar::term() {
  if (unknown08 & 1) {
    idle();
    unknown08 &= ~1;
  }
}

} // namespace event
