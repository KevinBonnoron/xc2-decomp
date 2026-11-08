#include "gf/game/gf_game_dead_camera.h"

#include "fw/fw_camera.h"

namespace gf {

GfDeadCamera::~GfDeadCamera() {
  if (unknown00.get() != nullptr) {
    if (fw::CameraManager::get() != nullptr) {
      fw::CameraManager::get()->unknown20[0].pop(unknown00, 0.0f);
    }
    unknown00 = nullptr;
  }
}

} // namespace gf
