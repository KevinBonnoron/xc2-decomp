#include "anm/anm_asm_speed_lerp_blend.h"

#include <float.h>

#include "anm/anm_asm_blender.h"
#include "anm/anm_asm_variable.h"
#include "anm/anm_control.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "anm/anm_util.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/vector.h"
#include <new>

namespace anm {

SpeedLerpBlendTree::SpeedLerpBlendTree(const ResStateData *pResStateData, const ResSpeedLerpTree *pResTree, mm::mtl::Vector<Variable> &variables,
                                       mm::mtl::IAllocator &allocator)
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

SpeedLerpBlendTree::~SpeedLerpBlendTree() {
  for (u32 i = 0; i < m_clipNum; i++) {
    m_pClips[i].destroyControl();
    m_pClips[i].~AsmClip();
  }
  m_pAllocator->deallocate(m_pClips);
  m_pClips = nullptr;
  m_clipNum = 0;
}

void SpeedLerpBlendTree::attach(AsmBlender *blender) {
  for (u32 i = 0; i < m_clipNum; i++) {
    blender->addClip(m_pClips[i]);
  }
}

void SpeedLerpBlendTree::dettach(AsmBlender *blender) {
  for (u32 i = 0; i < m_clipNum; i++) {
    blender->removeClip(m_pClips[i]);
  }
}

void SpeedLerpBlendTree::onEnter(AsmListener *listener) {
  initLoopCount();
  setSpeed(1.0f);
  notifyEnter(listener);
}

void SpeedLerpBlendTree::onLeave(AsmListener *listener) { notifyLeave(listener); }

void SpeedLerpBlendTree::update(f32 deltaTime, AsmListener *listener) {
  adjustSpeesAndWeight();
  updateLoopCount(m_pClips[0].update(deltaTime, listener));
  for (u32 i = 1; i < m_clipNum; i++) {
    m_pClips[i].update(deltaTime, nullptr);
  }
}

void SpeedLerpBlendTree::setLocalTime(f32 time) {
  m_pClips[0].setLocalTime(time);
  if (m_pClips[0].m_pControl == nullptr) {
    return;
  }
  f32 basePlayBackTime = Util::getPlayBackTime(*m_pClips[0].m_pControl->m_pBinding);
  for (u32 i = 1; i < m_clipNum; i++) {
    if (m_pClips[i].m_pControl != nullptr) {
      f32 playBackTime = Util::getPlayBackTime(*m_pClips[i].m_pControl->m_pBinding);
      f32 rate = basePlayBackTime > FLT_EPSILON ? playBackTime / basePlayBackTime : 0.0f;
      m_pClips[i].setLocalTime(rate * time);
    }
  }
}

f32 SpeedLerpBlendTree::getLocalTime() const { return m_pClips[0].getLocalTime(); }

void SpeedLerpBlendTree::onSetSpeed() { adjustSpeesAndWeight(); }

void SpeedLerpBlendTree::onSetWeight() { adjustSpeesAndWeight(); }

const AsmClip *SpeedLerpBlendTree::getBaseClip() const { return &m_pClips[0]; }

} // namespace anm
