#include "anm/anm_asm_blender.h"

#include "anm/anm_blender.h"
#include "anm/anm_control.h"
#include "anm/anm_factory.h"
#include "anm/anm_res_asm.h"
#include "anm/anm_res_clip_data.h"

namespace anm {

AsmBlender::AsmBlender() : m_pBlender(nullptr), m_skipSample(false) {}

AsmBlender::~AsmBlender() {}

void AsmBlender::setup(const ResASM &resAsm, mm::mtl::IAllocator &allocator) { m_pBlender = Factory::createBlender(resAsm.m_pSkeleton, &allocator); }

bool AsmBlender::addClip(AsmClip &clip) {
  if (clip.m_pControl == nullptr || !m_pBlender->addControl(clip.m_pControl)) {
    return false;
  }
  m_clips.push_back(&clip);
  m_skipSample = false;
  return true;
}

void AsmBlender::removeClip(AsmClip &clip) {
  if (clip.m_pControl != nullptr && m_pBlender->removeControl(clip.m_pControl)) {
    m_clips.erase(&clip);
  }
  m_skipSample = false;
}

AsmClip::AsmClip() : m_pControl(nullptr), m_pResClipData(nullptr) {}

AsmClip::~AsmClip() { destroyControl(); }

void AsmClip::destroyControl() {
  if (m_pControl != nullptr) {
    m_pControl->release();
    m_pControl = nullptr;
  }
  m_pResClipData = nullptr;
}

void AsmClip::createControl(const ResClipData &resClipData, mm::mtl::IAllocator &allocator) {
  m_pControl = Factory::createControl(resClipData.m_pBinding, &allocator);
  m_pResClipData = &resClipData;
}

void AsmClip::setLocalTime(f32 time) {
  if (m_pControl != nullptr) {
    m_pControl->setLocalTime(time);
  }
}

f32 AsmClip::getLocalTime() const {
  if (m_pControl != nullptr) {
    return m_pControl->m_localTime;
  }
  return 0.0f;
}

void AsmClip::setSpeed(f32 speed) {
  if (m_pControl != nullptr) {
    m_pControl->m_speed = m_pResClipData->m_pInfo->speed * speed;
  }
}

void AsmClip::setWeight(f32 weight) {
  if (m_pControl != nullptr) {
    m_pControl->m_weight = m_pResClipData->m_pInfo->weight * weight;
  }
}

} // namespace anm
