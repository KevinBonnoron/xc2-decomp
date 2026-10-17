#pragma once
#include <stddef.h>

#include "anm/anm_asm_blender.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_state_machine.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {
class AsmListener;
class Variable;

class ASMControl : public ReferenceObject {
public:
  ~ASMControl() override;
  void setListener(AsmListener *listener);
  void updateFrame(f32 deltaTime);
  void setVariable(const char *name, int value);
  bool getVariable(const char *name, int *value) const;
  void setVariable(const char *name, f32 value);
  bool getVariable(const char *name, f32 *value) const;

  u8 _18[0x20 - 0x18];
  AsmBlender m_blender;
  mm::mtl::Vector<Variable> m_variables;
  StateMachine m_stateMachines[7];
};

static_assert(offsetof(ASMControl, m_blender) == 0x20, "");
static_assert(offsetof(ASMControl, m_variables) == 0x48, "");
static_assert(offsetof(ASMControl, m_stateMachines) == 0x70, "");

} // namespace anm
