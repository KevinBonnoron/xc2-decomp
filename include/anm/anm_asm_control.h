#pragma once
#include <stddef.h>

#include "anm/anm_asm_blender.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_state_machine.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {
class AsmListener;
class ResASM;
class Variable;

class ASMControl : public ReferenceObject {
public:
  static const u32 LAYER_MAX = 7;

  ~ASMControl() override;
  void setListener(AsmListener *listener);
  void updateFrame(f32 deltaTime);
  void setVariable(const char *name, int value);
  bool getVariable(const char *name, int *value) const;
  void setVariable(const char *name, f32 value);
  bool getVariable(const char *name, f32 *value) const;
  void sampleTrucks(u32 count, QsTransform *transforms) { unknown20.sampleTrucks(count, transforms); }
  void sampleTrucksMS(u32 count, QsTransform *transforms) { unknown20.sampleTrucksMS(count, transforms); }

  const ResASM *unknown18;             // Inferred role: res asm; original member name unknown.
  AsmBlender unknown20;                // Inferred role: blender; original member name unknown.
  mm::mtl::Vector<Variable> unknown48; // Inferred role: variables; original member name unknown.
  StateMachine unknown70[LAYER_MAX];   // Inferred role: state machines; original member name unknown.
  QsTransform unknown380;              // Inferred role: locomotion; original member name unknown.
};

static_assert(offsetof(ASMControl, unknown18) == 0x18, "");
static_assert(offsetof(ASMControl, unknown20) == 0x20, "");
static_assert(offsetof(ASMControl, unknown48) == 0x48, "");
static_assert(offsetof(ASMControl, unknown70) == 0x70, "");
static_assert(offsetof(ASMControl, unknown380) == 0x380, "");

} // namespace anm
