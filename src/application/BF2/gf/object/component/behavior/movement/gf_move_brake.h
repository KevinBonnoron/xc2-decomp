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

class GfMoveBrakeControler {
public:
  // Field name and offset from the reflection built by createReflection.
  struct Param {
    f32 brake;
  };

  struct Packet {
    Packet() : m_paramAdapter() {}

    mm::Vec3 unknown00;              // Inferred role: velocity; original member name unknown.
    fw::ParamAdapter m_paramAdapter; // Inferred role: brake param; original member name unknown.
  };

  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  void update(const fw::UpdateInfo &info, Packet &packet);
};

static_assert(offsetof(GfMoveBrakeControler::Packet, m_paramAdapter) == 0x10, "");
static_assert(sizeof(GfMoveBrakeControler::Packet) == 0x20, "");
static_assert(sizeof(GfMoveBrakeControler::Param) == 0x04, "");

} // namespace gf
