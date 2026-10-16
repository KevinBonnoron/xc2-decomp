#pragma once
#include <stddef.h>

#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/gf_component.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComEvtAnim : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 2;

  void execCmd(const char *command);
  const char *getStateName() const;
  void setState(const char *state);
  void setVariable(const char *name, f32 value);
  void setVariable(const char *name, int value);
  bool easeIn(const char *name, AnimLayer layer);
  bool easeOut(const char *name, AnimLayer layer);
  bool setEaseWeight(const char *name, AnimLayer layer, f32 weight);
  bool setEaseSpeed(const char *name, AnimLayer layer, f32 speed);

  u8 _10[0x550 - 0x10];
  void *resAsm;
};

static_assert(offsetof(GfComEvtAnim, resAsm) == 0x550, "");

} // namespace gf
