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

class GfMoveJumpControler {
public:
  // Field names and offsets from the reflection built by createReflection.
  struct Param {
    f32 velocityMax;
    f32 accel;
    f32 angularVelMax;
    f32 angularAccel;
  };

  struct Packet {
    Packet() : m_paramAdapter() {}

    mm::Vec3 unknown00;              // Inferred role: velocity; original member name unknown.
    f32 unknown10;                   // Inferred role: angular velocity; original member name unknown.
    fw::ParamAdapter m_paramAdapter; // Inferred role: jump param; original member name unknown.
    f32 unknown20;                   // Inferred role: input power; original member name unknown.
    mm::Vec3 unknown30;              // Inferred role: input direction; original member name unknown.
    mm::Vec3 unknown40;              // Inferred role: current direction; original member name unknown.
  };

  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  void calcAngularVelocity(f32 deltaTime, Packet &packet);
  void calcVelocity(f32 deltaTime, Packet &packet);
  void update(const fw::UpdateInfo &info, Packet &packet);
};

static_assert(offsetof(GfMoveJumpControler::Param, accel) == 0x04, "");
static_assert(offsetof(GfMoveJumpControler::Param, angularVelMax) == 0x08, "");
static_assert(offsetof(GfMoveJumpControler::Param, angularAccel) == 0x0c, "");
static_assert(sizeof(GfMoveJumpControler::Param) == 0x10, "");
static_assert(offsetof(GfMoveJumpControler::Packet, unknown10) == 0x10, "");
static_assert(offsetof(GfMoveJumpControler::Packet, m_paramAdapter) == 0x18, "");
static_assert(offsetof(GfMoveJumpControler::Packet, unknown20) == 0x20, "");
static_assert(offsetof(GfMoveJumpControler::Packet, unknown30) == 0x30, "");
static_assert(offsetof(GfMoveJumpControler::Packet, unknown40) == 0x40, "");
static_assert(sizeof(GfMoveJumpControler::Packet) == 0x50, "");

} // namespace gf
