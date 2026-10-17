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

AddBlendTree::AddBlendTree(const ResStateData *pResStateData, const ResAddTree *pResTree, mm::mtl::Vector<Variable> &variables,
                           mm::mtl::IAllocator &allocator)
    : AsmState(pResStateData, allocator), m_pResTree(pResTree) {
  m_clipNum = pResStateData->m_clips.size();
  m_pClips = static_cast<AsmClip *>(allocator.allocate(m_clipNum * sizeof(AsmClip), 8));
  for (u32 i = 0; i < m_clipNum; i++) {
    AsmClip *clip = new (&m_pClips[i]) AsmClip;
    clip->createControl(pResStateData->m_clips[i], allocator);
  }
  m_pVariables = &variables;
}

AddBlendTree::~AddBlendTree() {
  for (u32 i = 0; i < m_clipNum; i++) {
    m_pClips[i].destroyControl();
    m_pClips[i].~AsmClip();
  }
  m_pAllocator->deallocate(m_pClips);
  m_pClips = nullptr;
  m_clipNum = 0;
}

void AddBlendTree::attach(AsmBlender *blender) {
  for (u32 i = 0; i < m_clipNum; i++) {
    blender->addClip(m_pClips[i]);
  }
}

void AddBlendTree::dettach(AsmBlender *blender) {
  for (u32 i = 0; i < m_clipNum; i++) {
    blender->removeClip(m_pClips[i]);
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
  updateLoopCount(m_pClips[0].update(deltaTime, listener));
  for (u32 i = 1; i < m_clipNum; i++) {
    m_pClips[i].update(deltaTime, nullptr);
  }
}

void AddBlendTree::adjustWeight() {
  u32 baseClipNum = m_pResTree->baseClipNum;
  for (u32 i = 0; i < baseClipNum; i++) {
    m_pClips[i].setWeight(m_weight);
  }
  for (u32 i = 0; i < m_pResTree->nodes.size(); i++) {
    const ResAddNode &node = m_pResTree->nodes[i];
    f32 value;
    (*m_pVariables)[node.variableIndex].getValue(&value);
    m_pClips[baseClipNum + i].setWeight(value * m_weight);
  }
}

void AddBlendTree::setLocalTime(f32 time) {
  for (u32 i = 0; i < m_clipNum; i++) {
    m_pClips[i].setLocalTime(time);
  }
}

f32 AddBlendTree::getLocalTime() const { return m_pClips[0].getLocalTime(); }

void AddBlendTree::onSetSpeed() {
  for (u32 i = 0; i < m_clipNum; i++) {
    m_pClips[i].setSpeed(m_speed);
  }
}

void AddBlendTree::onSetWeight() { adjustWeight(); }

const AsmClip *AddBlendTree::getBaseClip() const { return m_pClips; }

} // namespace anm
