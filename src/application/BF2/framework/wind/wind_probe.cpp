#include "framework/wind/wind_probe.h"

#include "framework/reference_frame.h"
#include "framework/wind/wind_manager.h"
#include "wnd/wnd.h"

namespace fw {

WindProbe::~WindProbe() {
  if (WindManager::get() != nullptr) {
    WindManager::get()->removeProbe(this);
  }

  if (unknown20 != nullptr) {
    unknown20->release();
    unknown20 = nullptr;
  }
}

} // namespace fw
