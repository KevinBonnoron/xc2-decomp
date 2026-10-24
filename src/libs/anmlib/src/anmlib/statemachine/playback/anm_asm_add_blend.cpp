#include "anm/anm_asm_add_blend.h"

#include "anm/anm_array-inl.h"
#include "anm/anm_asm_blender.h"
#include "anm/anm_asm_variable.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/vector.h"
#include <new>

namespace anm {

AddBlendTree::AddBlendTree(const ResStateData *pResStateData, const ResAddTree *pResTree, mm::mtl::Vector<Variable> &variables, mm::mtl::IAllocator &allocator)
    : AsmState(pResStateData, allocator), unknown30(pResTree) {
  unknown40 = pResStateData->unknown08.size();
  m_baseClip = static_cast<AsmClip *>(allocator.allocate(unknown40 * sizeof(AsmClip), 8));
  for (u32 i = 0; i < unknown40; i++) {
    AsmClip *clip = new (&m_baseClip[i]) AsmClip;
    clip->createControl(pResStateData->unknown08[i], allocator);
  }
  unknown48 = &variables;
}

AddBlendTree::~AddBlendTree() {
  for (u32 i = 0; i < unknown40; i++) {
    m_baseClip[i].destroyControl();
    m_baseClip[i].~AsmClip();
  }
  m_pAllocator->deallocate(m_baseClip);
  m_baseClip = nullptr;
  unknown40 = 0;
}

void AddBlendTree::attach(AsmBlender *blender) {
  for (u32 i = 0; i < unknown40; i++) {
    blender->addClip(m_baseClip[i]);
  }
}

void AddBlendTree::dettach(AsmBlender *blender) {
  for (u32 i = 0; i < unknown40; i++) {
    blender->removeClip(m_baseClip[i]);
  }
}

void AddBlendTree::onEnter(AsmListener *listener) {
  initLoopCount();
  setSpeed(1.0f);
  notifyEnter(listener);
}

void AddBlendTree::onLeave(AsmListener *listener) { notifyLeave(listener); }

void AddBlendTree::update(f32 deltaTime, AsmListener *listener) {
  adjustWeight();
  updateLoopCount(m_baseClip[0].update(deltaTime, listener));
  for (u32 i = 1; i < unknown40; i++) {
    m_baseClip[i].update(deltaTime, nullptr);
  }
}

void AddBlendTree::adjustWeight() {
  u32 baseClipNum = unknown30->unknown10;
  for (u32 i = 0; i < baseClipNum; i++) {
    m_baseClip[i].setWeight(unknown24);
  }
  for (u32 i = 0; i < unknown30->unknown18.size(); i++) {
    const ResAddNode &node = unknown30->unknown18[i];
    f32 value;
    (*unknown48)[node.variableIndex].getValue(&value);
    m_baseClip[baseClipNum + i].setWeight(value * unknown24);
  }
}

void AddBlendTree::setLocalTime(f32 time) {
  for (u32 i = 0; i < unknown40; i++) {
    m_baseClip[i].setLocalTime(time);
  }
}

f32 AddBlendTree::getLocalTime() const { return m_baseClip[0].getLocalTime(); }

void AddBlendTree::onSetSpeed() {
  for (u32 i = 0; i < unknown40; i++) {
    m_baseClip[i].setSpeed(unknown20);
  }
}

void AddBlendTree::onSetWeight() { adjustWeight(); }

const AsmClip *AddBlendTree::getBaseClip() const { return m_baseClip; }

} // namespace anm
