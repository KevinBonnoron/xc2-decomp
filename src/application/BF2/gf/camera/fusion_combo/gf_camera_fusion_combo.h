#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class FusionComboCamera : public fw::Camera {
public:
  static mm::mtl::RTTI m_rtti;

  ~FusionComboCamera() override;
  void onActivate() override;
  bool isPlayEnd() const;
  static f32 fastOut(f32 t);
  static f32 slowOut(f32 t);
  static f32 curve(f32 a, f32 b, f32 t);
  const mm::mtl::RTTI *getRTTI() const override;
  const char *getName() const override;

  u8 _a8[0x120 - 0xa8];
  f32 unknown120; // Inferred role: play time; original member name unknown.
  f32 unknown124; // Inferred role: play duration; original member name unknown.
  u8 _128[0x160 - 0x128];
};

static_assert(offsetof(FusionComboCamera, unknown120) == 0x120, "");
static_assert(offsetof(FusionComboCamera, unknown124) == 0x124, "");
static_assert(sizeof(FusionComboCamera) == 0x160, "");

} // namespace gf
