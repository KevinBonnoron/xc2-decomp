#include "event/chara_play_eva.h"

#include "event/chara_manager.h"
#include "event/motstm_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

void CharaPlayEva::term() {
  if ((unknown08 & FLAG_PLAY) != 0) {
    if (mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode() && unknown20 != nullptr) {
      mm::mtl::Singleton<MotstmManager>::getPtr()->free(unknown20);
    }
    unknown20 = nullptr;
    if (mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode() && unknown28 != nullptr) {
      mm::mtl::Singleton<MotstmManager>::getPtr()->free(unknown28);
    }
    unknown28 = nullptr;
    unknown08 &= ~FLAG_PLAY;
  }
}

} // namespace event
