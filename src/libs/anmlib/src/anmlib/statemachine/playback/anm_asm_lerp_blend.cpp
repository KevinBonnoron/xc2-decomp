#include "anm/anm_asm_lerp_blend.h"

#include "anm/anm_asm_blender.h"
#include "anm/anm_asm_variable.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/vector.h"
#include <new>

namespace anm {

LerpBlendTree::LerpBlendTree(const ResStateData *pResStateData, const ResLerpTree *pResTree, mm::mtl::Vector<Variable> &variables, mm::mtl::IAllocator &allocator)
    : AsmState(pResStateData, allocator), m_pResTree(pResTree) {
  m_clipNum = pResStateData->m_clips.size();
  m_pClips = static_cast<AsmClip *>(allocator.allocate(m_clipNum * sizeof(AsmClip), 8));
  for (u32 i = 0; i < m_clipNum; i++) {
    AsmClip *clip = new (&m_pClips[i]) AsmClip;
    clip->createControl(pResStateData->m_clips[i], allocator);
  }
  m_pVariable = &variables[m_pResTree->variableIndex];
  MM_ASSERT(m_pVariable->getVarType() == VAR_FLOAT);
}

LerpBlendTree::~LerpBlendTree() {
  for (u32 i = 0; i < m_clipNum; i++) {
    m_pClips[i].destroyControl();
    m_pClips[i].~AsmClip();
  }
  m_pAllocator->deallocate(m_pClips);
  m_pClips = nullptr;
  m_clipNum = 0;
}

void LerpBlendTree::attach(AsmBlender *blender) {
  for (u32 i = 0; i < m_clipNum; i++) {
    blender->addClip(m_pClips[i]);
  }
}

void LerpBlendTree::dettach(AsmBlender *blender) {
  for (u32 i = 0; i < m_clipNum; i++) {
    blender->removeClip(m_pClips[i]);
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
  updateLoopCount(m_pClips[0].update(deltaTime, listener));
  for (u32 i = 1; i < m_clipNum; i++) {
    m_pClips[i].update(deltaTime, nullptr);
  }
}

void LerpBlendTree::setLocalTime(f32 time) {
  for (u32 i = 0; i < m_clipNum; i++) {
    m_pClips[i].setLocalTime(time);
  }
}

f32 LerpBlendTree::getLocalTime() const { return m_pClips[0].getLocalTime(); }

void LerpBlendTree::onSetSpeed() {
  for (u32 i = 0; i < m_clipNum; i++) {
    m_pClips[i].setSpeed(m_speed);
  }
}

void LerpBlendTree::onSetWeight() { adjustWeight(); }

const AsmClip *LerpBlendTree::getBaseClip() const { return &m_pClips[0]; }

} // namespace anm
