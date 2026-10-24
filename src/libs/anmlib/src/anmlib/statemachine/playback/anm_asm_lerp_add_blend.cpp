#include "anm/anm_asm_lerp_add_blend.h"

#include "anm/anm_asm_blender.h"
#include "anm/anm_asm_variable.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/vector.h"
#include <new>

namespace anm {

LerpAddBlendTree::LerpAddBlendTree(const ResStateData *pResStateData, const ResLerpAddTree *pResTree, mm::mtl::Vector<Variable> &variables, mm::mtl::IAllocator &allocator)
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

LerpAddBlendTree::~LerpAddBlendTree() {
  for (u32 i = 0; i < unknown40; i++) {
    m_baseClip[i].destroyControl();
    m_baseClip[i].~AsmClip();
  }
  m_pAllocator->deallocate(m_baseClip);
  m_baseClip = nullptr;
  unknown40 = 0;
}

void LerpAddBlendTree::attach(AsmBlender *blender) {
  for (u32 i = 0; i < unknown40; i++) {
    blender->addClip(m_baseClip[i]);
  }
}

void LerpAddBlendTree::dettach(AsmBlender *blender) {
  for (u32 i = 0; i < unknown40; i++) {
    blender->removeClip(m_baseClip[i]);
  }
}

void LerpAddBlendTree::onEnter(AsmListener *listener) {
  initLoopCount();
  setSpeed(1.0f);
  notifyEnter(listener);
}

void LerpAddBlendTree::onLeave(AsmListener *listener) { notifyLeave(listener); }

void LerpAddBlendTree::update(f32 deltaTime, AsmListener *listener) {
  adjustWeight();
  updateLoopCount(m_baseClip[0].update(deltaTime, listener));
  for (u32 i = 1; i < unknown40; i++) {
    m_baseClip[i].update(deltaTime, nullptr);
  }
}

void LerpAddBlendTree::setLocalTime(f32 time) {
  for (u32 i = 0; i < unknown40; i++) {
    m_baseClip[i].setLocalTime(time);
  }
}

f32 LerpAddBlendTree::getLocalTime() const { return m_baseClip[0].getLocalTime(); }

void LerpAddBlendTree::onSetSpeed() {
  for (u32 i = 0; i < unknown40; i++) {
    m_baseClip[i].setSpeed(unknown20);
  }
}

void LerpAddBlendTree::onSetWeight() { adjustWeight(); }

const AsmClip *LerpAddBlendTree::getBaseClip() const { return &m_baseClip[0]; }

} // namespace anm
