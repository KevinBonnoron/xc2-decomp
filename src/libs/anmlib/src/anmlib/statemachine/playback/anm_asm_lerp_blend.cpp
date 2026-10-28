#include "anm/anm_asm_lerp_blend.h"

#include <algorithm>
#include <new>

#include "anm/anm_array.h"
#include "anm/anm_asm_blender.h"
#include "anm/anm_asm_variable.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/vector.h"

namespace anm {

LerpBlendTree::LerpBlendTree(const ResStateData *pResStateData, const ResLerpTree *pResTree, mm::mtl::Vector<Variable> &variables, mm::mtl::IAllocator &allocator)
    : AsmState(pResStateData, allocator), unknown30(pResTree) {
  unknown40 = pResStateData->unknown08.size();
  m_baseClip = static_cast<AsmClip *>(allocator.allocate(unknown40 * sizeof(AsmClip), 8));
  for (u32 i = 0; i < unknown40; i++) {
    AsmClip *clip = new (&m_baseClip[i]) AsmClip;
    clip->createControl(pResStateData->unknown08[i], allocator);
  }
  m_pVariable = &variables[unknown30->variableIndex];
  MM_ASSERT(m_pVariable->getVarType() == VAR_FLOAT);
}

LerpBlendTree::~LerpBlendTree() {
  for (u32 i = 0; i < unknown40; i++) {
    m_baseClip[i].destroyControl();
    m_baseClip[i].~AsmClip();
  }
  m_pAllocator->deallocate(m_baseClip);
  m_baseClip = nullptr;
  unknown40 = 0;
}

void LerpBlendTree::attach(AsmBlender *blender) {
  for (u32 i = 0; i < unknown40; i++) {
    blender->addClip(m_baseClip[i]);
  }
}

void LerpBlendTree::dettach(AsmBlender *blender) {
  for (u32 i = 0; i < unknown40; i++) {
    blender->removeClip(m_baseClip[i]);
  }
}

void LerpBlendTree::onEnter(AsmListener *listener) {
  initLoopCount();
  setSpeed(1.0f);
  notifyEnter(listener);
}

void LerpBlendTree::onLeave(AsmListener *listener) { notifyLeave(listener); }

void LerpBlendTree::update(f32 deltaTime, AsmListener *listener) {
  adjustWeight();
  updateLoopCount(m_baseClip[0].update(deltaTime, listener));
  for (u32 i = 1; i < unknown40; i++) {
    m_baseClip[i].update(deltaTime, nullptr);
  }
}

void LerpBlendTree::adjustWeight() {
  f32 value;
  m_pVariable->getValue(&value);
  u32 index = searchIndex(value);
  f32 upper = unknown30->unknown08[index].unknown00;
  f32 lower = unknown30->unknown08[index + 1].unknown00;
  f32 ratio = (value - lower) / (upper - lower);
  for (u32 i = 0; i < unknown40; i++) {
    if (i == index) {
      m_baseClip[i].setWeight(ratio * unknown24);
    } else if (i == index + 1) {
      m_baseClip[i].setWeight((1.0f - ratio) * unknown24);
    } else {
      m_baseClip[i].setWeight(0.0f);
    }
  }
}

void LerpBlendTree::setLocalTime(f32 time) {
  for (u32 i = 0; i < unknown40; i++) {
    m_baseClip[i].setLocalTime(time);
  }
}

f32 LerpBlendTree::getLocalTime() const { return m_baseClip[0].getLocalTime(); }

void LerpBlendTree::onSetSpeed() {
  for (u32 i = 0; i < unknown40; i++) {
    m_baseClip[i].setSpeed(unknown20);
  }
}

void LerpBlendTree::onSetWeight() { adjustWeight(); }

u32 LerpBlendTree::searchIndex(f32 value) const {
  const Array<ResLerpNode> &nodes = unknown30->unknown08;
  ArrayIterartor<const ResLerpNode> it = std::upper_bound(nodes.begin(), nodes.end(), value, CompLerpNode());
  if (it == nodes.begin()) {
    return 0;
  }
  u32 index = it - nodes.begin();
  u32 last = nodes.size() - 1;
  if (index >= last) {
    index = last;
  }
  return index - 1;
}

const AsmClip *LerpBlendTree::getBaseClip() const { return &m_baseClip[0]; }

} // namespace anm
