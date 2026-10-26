#include "fw/fw_camera.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {
struct UpdateInfo;

void CameraManager::update(const UpdateInfo &info) {
  if (unknown360.get() != nullptr) {
    unknown360->update(info);
  }

  for (u32 i = 0; i < LAYER_COUNT; i++) {
    unknown20[i].update(info);
  }
}

void CameraManager::Listener::onWkStandbyLogout() { unknown08->unknown368 = nullptr; }

} // namespace fw
