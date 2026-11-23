#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h"
#include "types.h"

namespace fw {
class Reflection;
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfMoveWaterRiseControler {
public:
  // Field names and offsets from the reflection built by createReflection.
  struct Param {
    f32 accel;
    f32 speedMax;
    f32 brake;
    f32 speedMin;
  };

  struct Packet {
    Packet() : m_paramAdapter(), unknown10(false) {}

    f32 unknown00;                   // Inferred role: vertical speed; original member name unknown.
    fw::ParamAdapter m_paramAdapter; // Inferred role: water rise param; original member name unknown.
    bool unknown10;                  // Inferred role: braking (within the rise brake height); original member name unknown.
  };

  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  void update(const fw::UpdateInfo &info, Packet &packet);
};

static_assert(offsetof(GfMoveWaterRiseControler::Param, speedMax) == 0x04, "");
static_assert(offsetof(GfMoveWaterRiseControler::Param, brake) == 0x08, "");
static_assert(offsetof(GfMoveWaterRiseControler::Param, speedMin) == 0x0c, "");
static_assert(sizeof(GfMoveWaterRiseControler::Param) == 0x10, "");
static_assert(offsetof(GfMoveWaterRiseControler::Packet, m_paramAdapter) == 0x08, "");
static_assert(offsetof(GfMoveWaterRiseControler::Packet, unknown10) == 0x10, "");
static_assert(sizeof(GfMoveWaterRiseControler::Packet) == 0x18, "");

} // namespace gf
