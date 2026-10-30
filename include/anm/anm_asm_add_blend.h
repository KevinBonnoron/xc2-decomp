#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_asm_state.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class AsmClip;
class Variable;
class ResStateData;

// Inferred role: res add node; original type name unknown.
struct unknown101 {
  u32 variableIndex;
  u8 _04[0x28 - 0x4];
};

struct ResAddTree {
  u8 _00[0x10];
  u32 unknown10; // Inferred role: base clip num; original member name unknown.
  u8 _14[0x18 - 0x14];
  Array<unknown101> unknown18; // Inferred role: nodes; original member name unknown.
};

static_assert(offsetof(ResAddTree, unknown18) == 0x18, "");

class AddBlendTree : public AsmState {
public:
  AddBlendTree(const ResStateData *pResStateData, const ResAddTree *pResTree, mm::mtl::Vector<Variable> &variables, mm::mtl::IAllocator &allocator);
  ~AddBlendTree() override;
  void attach(AsmBlender *blender) override;
  void dettach(AsmBlender *blender) override;
  void onEnter(AsmListener *listener) override;
  void onLeave(AsmListener *listener) override;
  void update(f32 deltaTime, AsmListener *listener) override;
  void adjustWeight();
  void setLocalTime(f32 time) override;
  f32 getLocalTime() const override;
  void onSetSpeed() override;
  void onSetWeight() override;
  const AsmClip *getBaseClip() const override;

  const ResAddTree *unknown30; // Inferred role: p res tree; original member name unknown.
  AsmClip *m_baseClip;
  u32 unknown40;                              // Inferred role: clip num; original member name unknown.
  const mm::mtl::Vector<Variable> *unknown48; // Inferred role: p variables; original member name unknown.
};

static_assert(offsetof(AddBlendTree, unknown30) == 0x30, "");
static_assert(offsetof(AddBlendTree, unknown48) == 0x48, "");

} // namespace anm
