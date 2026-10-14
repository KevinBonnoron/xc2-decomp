#pragma once
#include "fw/fw_camera.h"
#include "mm_mtl/rtti.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_OBJ_HANDLE;

class PlayerCameraTarget : public fw::CameraTarget {
public:
  static mm::mtl::RTTI m_rtti;

  static PlayerCameraTarget *create();

  u8 _10[0x70 - 0x10];
  GF_OBJ_HANDLE *player;
};

static_assert(offsetof(PlayerCameraTarget, player) == 0x70, "");

} // namespace gf
