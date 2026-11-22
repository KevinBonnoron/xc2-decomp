#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h"
#include "types.h"

namespace fw {
class Reflection;
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfMoveWaterSinkControler {
public:
  // Field names and offsets from the reflection built by createReflection.
  struct Param {
    f32 brake;
    f32 speedMin;
  };

  struct Packet {
    Packet() : m_paramAdapter() {}

    f32 unknown00;                   // Inferred role: vertical speed; original member name unknown.
    fw::ParamAdapter m_paramAdapter; // Inferred role: water sink param; original member name unknown.
  };

  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  void update(const fw::UpdateInfo &info, Packet &packet);
};

static_assert(offsetof(GfMoveWaterSinkControler::Param, speedMin) == 0x04, "");
static_assert(sizeof(GfMoveWaterSinkControler::Param) == 0x08, "");
static_assert(offsetof(GfMoveWaterSinkControler::Packet, m_paramAdapter) == 0x08, "");
static_assert(sizeof(GfMoveWaterSinkControler::Packet) == 0x10, "");

} // namespace gf
