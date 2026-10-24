#pragma once
#include <stddef.h>

#include "gf/object/component/gf_component.h"
#include "types.h"

namespace fw {
class WindProbe;
} // namespace fw
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComWind : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 9;

  struct SetupInfo {
    f32 radius;
    u32 group;
    bool isFollowFrame;
  };

  GfComWind();
  void setup(const SetupInfo &info);
  void cleanup();
  const mm::mtl::RTTI *getRTTI() const override;
  void changeLayer(u32 oldLayer, u32 newLayer) override;

  fw::WindProbe *unknown10; // Inferred role: probe; original member name unknown.
};

static_assert(offsetof(GfComWind, unknown10) == 0x10, "");

} // namespace gf
