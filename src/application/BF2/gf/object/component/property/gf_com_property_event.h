#pragma once
#include <stddef.h>

#include "gf/object/component/property/gf_com_property.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComPropertyEvent : public GfComProperty {
public:
  struct SetupInfo {};

  static mm::mtl::RTTI m_rtti;

  GfComPropertyEvent();
  void setup(const SetupInfo &info);
  void cleanup();
  void setMoveSpeed(f32 speed);
  f32 getMoveSpeed() const;
  const mm::mtl::RTTI *getRTTI() const override;

  f32 m_moveSpeed;
};

static_assert(offsetof(GfComPropertyEvent, m_moveSpeed) == 0x38, "");

} // namespace gf
