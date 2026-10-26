#pragma once
#include "gf/object/component/gf_component.h"
#include "types.h"

namespace mm {
struct Vec3;

namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

// Declaration rebuilt from the game's symbols (gf::GfComSound::stopSe, playSe2D); the component slot comes from the access offset 0x88.
class GfComSound : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 10;

  void stopSe(const char *name);
  bool playSe(const char *name, f32 volume, const mm::Vec3 &offset, bool isFollow);
  void playSe2D(const char *name, f32 volume, bool, bool);
  int getAttributeVariable() const;
  void setAttributeVariable(int attribute);
};

} // namespace gf
