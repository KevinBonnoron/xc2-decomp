#include "framework/wind/wind_impluse.h"

#include "framework/wind/wind_manager.h"
#include "fw/fw_update_info.h"
#include "wnd/wnd.h"

namespace fw {

WindImpluse::~WindImpluse() {
  if (WindManager::get() != nullptr) {
    WindManager::get()->removeImpluse(this);
  }
}

bool WindImpluse::update(const UpdateInfo &info) {
  unknown28 += info.unknown04;
  if (unknown20 != nullptr) {
    f32 ratio = unknown28 / unknown2c;
    f32 clamped = ratio;
    if (1.0f < ratio) {
      clamped = 1.0f;
    }

    f32 fade = 1.0f - clamped;
    if (ratio < 0.0f) {
      fade = 1.0f;
    }

    unknown20->unknown88 = unknown30 * fade;
  }

  return unknown28 < unknown2c;
}

} // namespace fw
