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

class GfMoveWalkControler {
public:
  // Field names and offsets from the reflection built by createReflection.
  struct Param {
    f32 velocity;
    f32 angularVelMin;
    f32 angularVelMax;
  };

  struct Packet {
    Packet() : unknown00(mm::Vec3::zero), unknown10(0.0f), m_paramAdapter(), unknown20(mm::Vec3::zero), unknown30(mm::Vec3::zero), unknown40(1.0f) {}

    mm::Vec3 unknown00;              // Inferred role: velocity; original member name unknown.
    f32 unknown10;                   // Inferred role: angular velocity; original member name unknown.
    fw::ParamAdapter m_paramAdapter; // Inferred role: walk param; original member name unknown.
    mm::Vec3 unknown20;              // Inferred role: target direction; original member name unknown.
    mm::Vec3 unknown30;              // Inferred role: current direction; original member name unknown.
    f32 unknown40;                   // Inferred role: speed ratio; original member name unknown.
  };

  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  void enter(Packet &packet);
  void update(const fw::UpdateInfo &info, Packet &packet);
};

static_assert(offsetof(GfMoveWalkControler::Param, angularVelMax) == 0x08, "");
static_assert(sizeof(GfMoveWalkControler::Param) == 0x0c, "");
static_assert(offsetof(GfMoveWalkControler::Packet, unknown10) == 0x10, "");
static_assert(offsetof(GfMoveWalkControler::Packet, m_paramAdapter) == 0x18, "");
static_assert(offsetof(GfMoveWalkControler::Packet, unknown20) == 0x20, "");
static_assert(offsetof(GfMoveWalkControler::Packet, unknown30) == 0x30, "");
static_assert(offsetof(GfMoveWalkControler::Packet, unknown40) == 0x40, "");
static_assert(sizeof(GfMoveWalkControler::Packet) == 0x50, "");

} // namespace gf
