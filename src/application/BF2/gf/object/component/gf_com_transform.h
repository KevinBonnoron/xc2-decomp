#pragma once
#include "gf/object/component/gf_component.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
struct Quat;
struct Vec3;
} // namespace mm

namespace gf {

class GfComTransform : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 0;

  void setPosition(const mm::Vec3 &position);
  const mm::Vec3 &getPosition() const;
  void setRotation(const mm::Quat &rotation);
  const mm::Quat &getRotation() const;
};

} // namespace gf
