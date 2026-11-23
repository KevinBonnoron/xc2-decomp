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

class GfMoveSlideControler {
public:
  // Field names and offsets from the reflection built by createReflection.
  struct Param {
    f32 sideVel;
    f32 frontBrake;
    f32 angularVelMin;
    f32 angularVelMaxs;
  };

  struct Packet {
    Packet()
        : unknown00(mm::Vec3::zero), unknown10(0.0f), unknown14(0.0f), m_paramAdapter(), unknown20(0.0f), unknown30(mm::Vec3::zero), unknown40(mm::Vec3::zero), unknown50(mm::Vec3::zero),
          unknown60(10.0f) {}

    mm::Vec3 unknown00;              // Inferred role: velocity; original member name unknown.
    f32 unknown10;                   // Inferred role: angular velocity; original member name unknown.
    f32 unknown14;                   // Inferred role: slide speed; original member name unknown.
    fw::ParamAdapter m_paramAdapter; // Inferred role: slide move param; original member name unknown.
    f32 unknown20;                   // Inferred role: input power; original member name unknown.
    mm::Vec3 unknown30;              // Inferred role: input direction; original member name unknown.
    mm::Vec3 unknown40;              // Inferred role: current direction; original member name unknown.
    mm::Vec3 unknown50;              // Inferred role: slide direction; original member name unknown.
    f32 unknown60;                   // Inferred role: slide speed lower limit; original member name unknown.
  };

  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  void update(const fw::UpdateInfo &info, Packet &packet);
};

static_assert(offsetof(GfMoveSlideControler::Param, frontBrake) == 0x04, "");
static_assert(offsetof(GfMoveSlideControler::Param, angularVelMin) == 0x08, "");
static_assert(offsetof(GfMoveSlideControler::Param, angularVelMaxs) == 0x0c, "");
static_assert(sizeof(GfMoveSlideControler::Param) == 0x10, "");
static_assert(offsetof(GfMoveSlideControler::Packet, unknown10) == 0x10, "");
static_assert(offsetof(GfMoveSlideControler::Packet, unknown14) == 0x14, "");
static_assert(offsetof(GfMoveSlideControler::Packet, m_paramAdapter) == 0x18, "");
static_assert(offsetof(GfMoveSlideControler::Packet, unknown20) == 0x20, "");
static_assert(offsetof(GfMoveSlideControler::Packet, unknown30) == 0x30, "");
static_assert(offsetof(GfMoveSlideControler::Packet, unknown40) == 0x40, "");
static_assert(offsetof(GfMoveSlideControler::Packet, unknown50) == 0x50, "");
static_assert(offsetof(GfMoveSlideControler::Packet, unknown60) == 0x60, "");
static_assert(sizeof(GfMoveSlideControler::Packet) == 0x70, "");

} // namespace gf
