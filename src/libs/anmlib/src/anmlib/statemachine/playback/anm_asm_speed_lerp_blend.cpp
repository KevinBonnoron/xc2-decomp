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

SpeedLerpBlendTree::SpeedLerpBlendTree(const ResStateData *pResStateData, const ResSpeedLerpTree *pResTree, mm::mtl::Vector<Variable> &variables, mm::mtl::IAllocator &allocator)
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

SpeedLerpBlendTree::~SpeedLerpBlendTree() {
  for (u32 i = 0; i < unknown40; i++) {
    m_baseClip[i].destroyControl();
    m_baseClip[i].~AsmClip();
  }
  m_pAllocator->deallocate(m_baseClip);
  m_baseClip = nullptr;
  unknown40 = 0;
}

void SpeedLerpBlendTree::attach(AsmBlender *blender) {
  for (u32 i = 0; i < unknown40; i++) {
    blender->addClip(m_baseClip[i]);
  }
}

void SpeedLerpBlendTree::dettach(AsmBlender *blender) {
  for (u32 i = 0; i < unknown40; i++) {
    blender->removeClip(m_baseClip[i]);
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
  updateLoopCount(m_baseClip[0].update(deltaTime, listener));
  for (u32 i = 1; i < unknown40; i++) {
    m_baseClip[i].update(deltaTime, nullptr);
  }
}

void SpeedLerpBlendTree::setLocalTime(f32 time) {
  m_baseClip[0].setLocalTime(time);
  if (m_baseClip[0].unknown10 == nullptr) {
    return;
  }
  f32 basePlayBackTime = Util::getPlayBackTime(*m_baseClip[0].unknown10->m_pBinding);
  for (u32 i = 1; i < unknown40; i++) {
    if (m_baseClip[i].unknown10 != nullptr) {
      f32 playBackTime = Util::getPlayBackTime(*m_baseClip[i].unknown10->m_pBinding);
      f32 rate = basePlayBackTime > FLT_EPSILON ? playBackTime / basePlayBackTime : 0.0f;
      m_baseClip[i].setLocalTime(rate * time);
    }
  }
}

f32 SpeedLerpBlendTree::getLocalTime() const { return m_baseClip[0].getLocalTime(); }

void SpeedLerpBlendTree::onSetSpeed() { adjustSpeesAndWeight(); }

void SpeedLerpBlendTree::onSetWeight() { adjustSpeesAndWeight(); }

const AsmClip *SpeedLerpBlendTree::getBaseClip() const { return &m_baseClip[0]; }

} // namespace anm
