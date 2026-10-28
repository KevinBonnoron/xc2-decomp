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

struct ResSpeedLerpNode {
  f32 unknown00; // Inferred role: variable value of the node; original member name unknown.
  u8 _04[0x28 - 0x04];
};

struct ResSpeedLerpTree {
  u8 _00[0x4];
  u32 variableIndex;
  Array<ResSpeedLerpNode> unknown08; // Inferred role: nodes, sorted by descending value; original member name unknown.
};

static_assert(offsetof(ResSpeedLerpTree, unknown08) == 0x08, "");
static_assert(sizeof(ResSpeedLerpNode) == 0x28, "");

class SpeedLerpBlendTree : public AsmState {
public:
  SpeedLerpBlendTree(const ResStateData *pResStateData, const ResSpeedLerpTree *pResTree, mm::mtl::Vector<Variable> &variables, mm::mtl::IAllocator &allocator);
  ~SpeedLerpBlendTree() override;
  void attach(AsmBlender *blender) override;
  void dettach(AsmBlender *blender) override;
  void onEnter(AsmListener *listener) override;
  void onLeave(AsmListener *listener) override;
  void update(f32 deltaTime, AsmListener *listener) override;
  void adjustSpeesAndWeight();
  void setLocalTime(f32 time) override;
  f32 getLocalTime() const override;
  void onSetSpeed() override;
  void onSetWeight() override;
  u32 searchIndex(f32 value) const;
  const AsmClip *getBaseClip() const override;

  const ResSpeedLerpTree *unknown30; // Inferred role: p res tree; original member name unknown.
  AsmClip *m_baseClip;
  u32 unknown40; // Inferred role: clip num; original member name unknown.
  Variable *m_pVariable;
};

static_assert(offsetof(SpeedLerpBlendTree, unknown30) == 0x30, "");
static_assert(offsetof(SpeedLerpBlendTree, m_pVariable) == 0x48, "");

} // namespace anm
