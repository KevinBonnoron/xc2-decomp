#include "anm/anm_asm_speed_lerp_blend.h"

#include <algorithm>
#include <float.h>
#include <new>

#include "anm/anm_array.h"
#include "anm/anm_asm_blender.h"
#include "anm/anm_asm_lerp_blend.h"
#include "anm/anm_asm_variable.h"
#include "anm/anm_control.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "anm/anm_util.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/vector.h"

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

void SpeedLerpBlendTree::adjustSpeesAndWeight() {
  MM_ASSERT(m_pVariable);
  f32 value;
  m_pVariable->getValue(&value);
  u32 index = searchIndex(value);
  if (m_baseClip[index].unknown10 != nullptr && m_baseClip[index + 1].unknown10 != nullptr) {
    f32 lower = unknown30->unknown08[index].unknown00;
    f32 upper = unknown30->unknown08[index + 1].unknown00;
    f32 ratio = mm::clamp((value - lower) / (upper - lower), 0.0f, 1.0f);
    f32 lowerPlayBackTime = Util::getPlayBackTime(*m_baseClip[index].unknown10->m_pBinding);
    f32 upperPlayBackTime = Util::getPlayBackTime(*m_baseClip[index + 1].unknown10->m_pBinding);
    f32 upperRate = lowerPlayBackTime > FLT_EPSILON ? upperPlayBackTime / lowerPlayBackTime : 0.0f;
    f32 blendedSpeed = lower * (1.0f - ratio) + ratio * (upper * upperRate);
    f32 baseSpeed = mm::fabs(blendedSpeed) > FLT_EPSILON ? value / blendedSpeed : 0.0f;
    for (u32 i = 0; i < unknown40; i++) {
      if (i == index) {
        m_baseClip[index].setWeight((1.0f - ratio) * unknown24);
        m_baseClip[index].setSpeed(baseSpeed * unknown20);
      } else if (i == index + 1) {
        m_baseClip[i].setWeight(ratio * unknown24);
        m_baseClip[i].setSpeed(upperRate * baseSpeed * unknown20);
      } else {
        m_baseClip[i].setWeight(0.0f);
        if (m_baseClip[i].unknown10 != nullptr) {
          f32 playBackTime = Util::getPlayBackTime(*m_baseClip[i].unknown10->m_pBinding);
          f32 rate = playBackTime > FLT_EPSILON ? baseSpeed * (lowerPlayBackTime / playBackTime) : 0.0f;
          m_baseClip[i].setSpeed(rate * unknown20);
        }
      }
    }
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

u32 SpeedLerpBlendTree::searchIndex(f32 value) const {
  const Array<ResSpeedLerpNode> &nodes = unknown30->unknown08;
  ArrayIterartor<const ResSpeedLerpNode> it = std::upper_bound(nodes.begin(), nodes.end(), value, CompLerpNode());
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

const AsmClip *SpeedLerpBlendTree::getBaseClip() const { return &m_baseClip[0]; }

} // namespace anm
