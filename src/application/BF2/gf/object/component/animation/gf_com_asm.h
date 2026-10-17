#pragma once
#include "gf/object/component/gf_component.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

enum AnimLayer {
  ANIM_LAYER_BASE = 0,
  ANIM_LAYER_HEAD = 2,
  ANIM_LAYER_EYE = 3,
  ANIM_LAYER_LIP = 4,
  ANIM_LAYER_BROW = 5,
};

class GfComAsm : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 2;

  const char *getStateName(AnimLayer layer) const;
  bool isLoop(AnimLayer layer) const;
  void easeIn(const char *state, f32 time, AnimLayer layer);
  void easeOut(const char *state, f32 time, AnimLayer layer);
  bool isActiveAdditiveState(const char *state, AnimLayer layer);
  void setWeightAdditiveState(const char *state, f32 weight, AnimLayer layer);
  void setSpeedAdditiveState(const char *state, f32 speed, AnimLayer layer);
};

} // namespace gf
