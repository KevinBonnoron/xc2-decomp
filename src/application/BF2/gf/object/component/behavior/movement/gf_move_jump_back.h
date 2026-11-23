#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace fw {
class Reflection;
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfMoveJumpBackControler {
public:
  // Field names and offsets from the reflection built by createReflection.
  struct Param {
    f32 velocityMax;
    f32 accel;
  };

  struct Packet {
    Packet() : m_paramAdapter() {}

    mm::Vec3 unknown00;              // Inferred role: velocity; original member name unknown.
    fw::ParamAdapter m_paramAdapter; // Inferred role: jump back param; original member name unknown.
    f32 unknown18;                   // Inferred role: velocity ratio; original member name unknown.
    mm::Vec3 unknown20;              // Inferred role: direction; original member name unknown.
  };

  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  void update(const fw::UpdateInfo &info, Packet &packet);
};

static_assert(offsetof(GfMoveJumpBackControler::Param, accel) == 0x04, "");
static_assert(sizeof(GfMoveJumpBackControler::Param) == 0x08, "");
static_assert(offsetof(GfMoveJumpBackControler::Packet, m_paramAdapter) == 0x10, "");
static_assert(offsetof(GfMoveJumpBackControler::Packet, unknown18) == 0x18, "");
static_assert(offsetof(GfMoveJumpBackControler::Packet, unknown20) == 0x20, "");
static_assert(sizeof(GfMoveJumpBackControler::Packet) == 0x30, "");

} // namespace gf
