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

struct GF_OBJ_HANDLE;

class PlayerCameraTarget : public fw::CameraTarget {
public:
  static mm::mtl::RTTI m_rtti;

  static PlayerCameraTarget *create();

  u8 _10[0x70 - 0x10];
  GF_OBJ_HANDLE *unknown70; // Inferred role: player; original member name unknown.
};

static_assert(offsetof(PlayerCameraTarget, unknown70) == 0x70, "");

} // namespace gf
