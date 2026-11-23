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

class GfMoveRunControler {
public:
  // Field names and offsets from the reflection built by createReflection.
  struct Param {
    f32 velocityMin;
    f32 velocityMax;
    f32 accel;
    f32 brake;
    f32 angularVelMin;
    f32 angularVelMax;
  };

  struct Packet {
    Packet() : unknown00(mm::Vec3::zero), unknown10(0.0f), m_paramAdapter(), unknown20(0.0f), unknown30(mm::Vec3::zero), unknown40(mm::Vec3::zero), unknown50(1.0f), unknown54(0.0f) {}

    mm::Vec3 unknown00;              // Inferred role: velocity; original member name unknown.
    f32 unknown10;                   // Inferred role: angular velocity; original member name unknown.
    fw::ParamAdapter m_paramAdapter; // Inferred role: run param; original member name unknown.
    f32 unknown20;                   // Inferred role: input power; original member name unknown.
    mm::Vec3 unknown30;              // Inferred role: input direction; original member name unknown.
    mm::Vec3 unknown40;              // Inferred role: current direction; original member name unknown.
    f32 unknown50;                   // Inferred role: speed ratio; original member name unknown.
    f32 unknown54;                   // Inferred role: speed offset; original member name unknown.
  };

  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  void calcAngularVelocity(f32 deltaTime, Packet &packet);
  void calcVelocity(f32 deltaTime, Packet &packet);
  void enter(Packet &packet, bool isInherit);
  void update(const fw::UpdateInfo &info, Packet &packet);
};

static_assert(offsetof(GfMoveRunControler::Param, velocityMax) == 0x04, "");
static_assert(offsetof(GfMoveRunControler::Param, accel) == 0x08, "");
static_assert(offsetof(GfMoveRunControler::Param, brake) == 0x0c, "");
static_assert(offsetof(GfMoveRunControler::Param, angularVelMin) == 0x10, "");
static_assert(offsetof(GfMoveRunControler::Param, angularVelMax) == 0x14, "");
static_assert(sizeof(GfMoveRunControler::Param) == 0x18, "");
static_assert(offsetof(GfMoveRunControler::Packet, unknown10) == 0x10, "");
static_assert(offsetof(GfMoveRunControler::Packet, m_paramAdapter) == 0x18, "");
static_assert(offsetof(GfMoveRunControler::Packet, unknown20) == 0x20, "");
static_assert(offsetof(GfMoveRunControler::Packet, unknown30) == 0x30, "");
static_assert(offsetof(GfMoveRunControler::Packet, unknown40) == 0x40, "");
static_assert(offsetof(GfMoveRunControler::Packet, unknown50) == 0x50, "");
static_assert(offsetof(GfMoveRunControler::Packet, unknown54) == 0x54, "");
static_assert(sizeof(GfMoveRunControler::Packet) == 0x60, "");

} // namespace gf
