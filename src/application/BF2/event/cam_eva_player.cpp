#include "event/cam_eva_player.h"

#include "event/cam_base.h"
#include "event/memory_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_cam.h"

namespace event {

CamEvaPlayer::CamEvaPlayer() : unknown08(nullptr), unknown10(nullptr) {}

CamEvaPlayer::~CamEvaPlayer() { stop(); }

void CamEvaPlayer::stop() {
  if (unknown10 != nullptr) {
    unknown10->clear();
    if (unknown10 != nullptr) {
      delete unknown10;
      unknown10 = nullptr;
    }
  }
  unknown08 = nullptr;
}

void CamEvaPlayer::play(CamBase *cam, void *data, const mm::Vec3 &offset) {
  stop();
  unknown10 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) RchaCam;
  unknown08 = cam;
  unknown10->setup(mtl::ALLOC_HANDLE(), data);
  unknown18 = 0.0f;
  unknown20 = offset;
  unknown30 = static_cast<EVT_nearfar>(0);
}

void CamEvaPlayer::setNearfar(EVT_nearfar nearfar) {
  unknown08->setNearFar(CamUtil::id2near(nearfar), CamUtil::id2far(nearfar));
  unknown30 = nearfar;
}

} // namespace event
