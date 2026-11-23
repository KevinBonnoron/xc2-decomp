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

class GfMoveTurnControler {
public:
  // Field names and offsets from the reflection built by createReflection.
  struct Param {
    f32 angularVelMin;
    f32 angularVelMax;
  };

  struct Packet {
    Packet() : m_paramAdapter() {}

    f32 unknown00;                   // Inferred role: angular velocity; original member name unknown.
    fw::ParamAdapter m_paramAdapter; // Inferred role: turn param; original member name unknown.
    mm::Vec3 unknown10;              // Inferred role: target direction; original member name unknown.
    mm::Vec3 unknown20;              // Inferred role: current direction; original member name unknown.
  };

  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  void update(const fw::UpdateInfo &info, Packet &packet);
};

static_assert(offsetof(GfMoveTurnControler::Param, angularVelMax) == 0x04, "");
static_assert(sizeof(GfMoveTurnControler::Param) == 0x08, "");
static_assert(offsetof(GfMoveTurnControler::Packet, m_paramAdapter) == 0x08, "");
static_assert(offsetof(GfMoveTurnControler::Packet, unknown10) == 0x10, "");
static_assert(offsetof(GfMoveTurnControler::Packet, unknown20) == 0x20, "");
static_assert(sizeof(GfMoveTurnControler::Packet) == 0x30, "");

} // namespace gf
