#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "types.h"

namespace gf {

class ShipRollPlugin : public fw::CameraPlugin {
public:
  ~ShipRollPlugin() override;
  virtual void update(fw::Camera *camera);
  static bool isRollEnable();
  static bool isPitchEnable();

  f32 unknown20;      // Inferred role: roll angle; original member name unknown.
  f32 unknown24;      // Inferred role: pitch angle; original member name unknown.
  f32 unknown28;      // Inferred role: roll cycle angle; original member name unknown.
  f32 unknown2c;      // Inferred role: roll amplitude; original member name unknown.
  bool unknown30;     // Inferred role: roll goes back; original member name unknown.
  bool m_rollEnable;  // Evidence: read by isRollEnable.
  f32 unknown34;      // Inferred role: pitch cycle angle; original member name unknown.
  f32 unknown38;      // Inferred role: pitch amplitude; original member name unknown.
  bool unknown3c;     // Inferred role: pitch goes back; original member name unknown.
  bool m_pitchEnable; // Evidence: read by isPitchEnable.
};

static_assert(offsetof(ShipRollPlugin, unknown20) == 0x20, "");
static_assert(offsetof(ShipRollPlugin, unknown28) == 0x28, "");
static_assert(offsetof(ShipRollPlugin, unknown30) == 0x30, "");
static_assert(offsetof(ShipRollPlugin, m_rollEnable) == 0x31, "");
static_assert(offsetof(ShipRollPlugin, unknown34) == 0x34, "");
static_assert(offsetof(ShipRollPlugin, unknown3c) == 0x3c, "");
static_assert(offsetof(ShipRollPlugin, m_pitchEnable) == 0x3d, "");
static_assert(sizeof(ShipRollPlugin) == 0x40, "");

} // namespace gf
