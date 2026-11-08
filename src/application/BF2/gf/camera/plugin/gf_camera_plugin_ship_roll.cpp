// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/camera/plugin/gf_camera_plugin_ship_roll.cpp.
#include "gf/camera/plugin/gf_camera_plugin_ship_roll.h"

#include "mm_mtl/intrusive_ptr.h"

namespace gf {

// Inferred role: the plugin pushed on the camera layer; no game symbol, original name unknown.
static mm::mtl::IntrusivePtr<ShipRollPlugin> unknown001;

ShipRollPlugin::~ShipRollPlugin() {}

bool ShipRollPlugin::isRollEnable() {
  if (unknown001.get() != nullptr) {
    return unknown001.get()->m_rollEnable;
  }
  return false;
}

bool ShipRollPlugin::isPitchEnable() {
  if (unknown001.get() != nullptr) {
    return unknown001.get()->m_pitchEnable;
  }
  return false;
}

} // namespace gf
