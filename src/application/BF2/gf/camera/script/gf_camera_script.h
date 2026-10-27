#pragma once

#include "fw/fw_camera.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class ScriptCameraEntity : public fw::Camera {
public:
  static mm::mtl::RTTI m_rtti;

  ~ScriptCameraEntity() override;
  void onActivate() override;
  const mm::mtl::RTTI *getRTTI() const override;
  const char *getName() const override;

  u8 _a8[0x120 - 0xa8];
};

static_assert(sizeof(ScriptCameraEntity) == 0x120, "");

} // namespace gf
