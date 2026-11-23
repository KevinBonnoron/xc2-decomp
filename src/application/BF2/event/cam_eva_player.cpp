#include "event/cam_eva_player.h"

#include "event/cam_base.h"
#include "event/memory_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_cam.h"

namespace event {

CamEvaPlayer::CamEvaPlayer() : m_camBase(nullptr), m_rchaCam(nullptr) {}

CamEvaPlayer::~CamEvaPlayer() { stop(); }

void CamEvaPlayer::stop() {
  if (m_rchaCam != nullptr) {
    m_rchaCam->clear();
    if (m_rchaCam != nullptr) {
      delete m_rchaCam;
      m_rchaCam = nullptr;
    }
  }
  m_camBase = nullptr;
}

void CamEvaPlayer::play(CamBase *cam, void *data, const mm::Vec3 &offset) {
  stop();
  m_rchaCam = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) RchaCam;
  m_camBase = cam;
  m_rchaCam->setup(mtl::ALLOC_HANDLE(), data);
  unknown18 = 0.0f;
  unknown20 = offset;
  unknown30 = static_cast<EVT_nearfar>(0);
}

void CamEvaPlayer::setNearfar(EVT_nearfar nearfar) {
  m_camBase->setNearFar(CamUtil::id2near(nearfar), CamUtil::id2far(nearfar));
  unknown30 = nearfar;
}

} // namespace event
