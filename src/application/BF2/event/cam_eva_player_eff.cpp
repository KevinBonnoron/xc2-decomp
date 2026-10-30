#include "event/cam_eva_player_eff.h"

#include "event/memory_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_cam_eff.h"

namespace event {

CamEvaPlayerEff::CamEvaPlayerEff() : unknown08(nullptr) {}

CamEvaPlayerEff::~CamEvaPlayerEff() { stop(); }

void CamEvaPlayerEff::stop() {
  if (unknown08 != nullptr) {
    unknown08->clear();
    if (unknown08 != nullptr) {
      delete unknown08;
      unknown08 = nullptr;
    }
  }
}

void CamEvaPlayerEff::play(void *data) {
  stop();
  unknown08 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) RchaCamEff;
  unknown08->setup(mtl::ALLOC_HANDLE(), data);
  unknown10 = 0.0f;
}

} // namespace event
