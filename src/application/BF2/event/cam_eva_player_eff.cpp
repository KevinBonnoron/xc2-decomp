#include "event/cam_eva_player_eff.h"

#include "event/memory_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_cam_eff.h"

namespace event {

CamEvaPlayerEff::CamEvaPlayerEff() : m_rchaCamEff(nullptr) {}

CamEvaPlayerEff::~CamEvaPlayerEff() { stop(); }

void CamEvaPlayerEff::stop() {
  if (m_rchaCamEff != nullptr) {
    m_rchaCamEff->clear();
    if (m_rchaCamEff != nullptr) {
      delete m_rchaCamEff;
      m_rchaCamEff = nullptr;
    }
  }
}

void CamEvaPlayerEff::play(void *data) {
  stop();
  m_rchaCamEff = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) RchaCamEff;
  m_rchaCamEff->setup(mtl::ALLOC_HANDLE(), data);
  unknown10 = 0.0f;
}

} // namespace event
