#include "event/chara_play_eva.h"

#include "event/chara_manager.h"
#include "event/motstm_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

void CharaPlayEva::term() {
  if ((flags & FLAG_PLAY) != 0) {
    if (mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode() && data != nullptr) {
      mm::mtl::Singleton<MotstmManager>::getPtr()->free(data);
    }
    data = nullptr;
    if (mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode() && weaponData != nullptr) {
      mm::mtl::Singleton<MotstmManager>::getPtr()->free(weaponData);
    }
    weaponData = nullptr;
    flags &= ~FLAG_PLAY;
  }
}

} // namespace event
