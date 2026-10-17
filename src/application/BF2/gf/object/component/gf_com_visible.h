#pragma once
#include <stddef.h>

#include "gf/object/component/gf_component.h"
#include "types.h"

namespace fw {
class VisibleObject;
} // namespace fw
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComVisible : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;

  struct SetupInfo {};

  GfComVisible();
  void setup(const SetupInfo &info);
  void cleanup();
  void changeLayer(u32 oldLayer, u32 newLayer) override;
  bool isRender() const;
  const mm::mtl::RTTI *getRTTI() const override;

  fw::VisibleObject *visible;
};

static_assert(offsetof(GfComVisible, visible) == 0x10, "");

} // namespace gf
