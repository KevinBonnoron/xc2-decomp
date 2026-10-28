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

struct ResLerpNode {
  f32 unknown00; // Inferred role: variable value of the node; original member name unknown.
  u8 _04[0x28 - 0x04];
};

// Orders a variable value against the nodes of a lerp tree; shared with SpeedLerpBlendTree.
struct CompLerpNode {
  template <typename Node> bool operator()(f32 value, const Node &node) const { return value < node.unknown00; }
};

struct ResLerpTree {
  u8 _00[0x4];
  u32 variableIndex;
  Array<ResLerpNode> unknown08; // Inferred role: nodes, sorted by descending value; original member name unknown.
};

static_assert(offsetof(ResLerpTree, unknown08) == 0x08, "");
static_assert(sizeof(ResLerpNode) == 0x28, "");

class LerpBlendTree : public AsmState {
public:
  LerpBlendTree(const ResStateData *pResStateData, const ResLerpTree *pResTree, mm::mtl::Vector<Variable> &variables, mm::mtl::IAllocator &allocator);
  ~LerpBlendTree() override;
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
  u32 searchIndex(f32 value) const;
  const AsmClip *getBaseClip() const override;

  const ResLerpTree *unknown30; // Inferred role: p res tree; original member name unknown.
  AsmClip *m_baseClip;
  u32 unknown40; // Inferred role: clip num; original member name unknown.
  Variable *m_pVariable;
};

static_assert(offsetof(LerpBlendTree, unknown30) == 0x30, "");
static_assert(offsetof(LerpBlendTree, m_pVariable) == 0x48, "");

} // namespace anm
