#include "anm/anm_asm_blender.h"

#include "anm/anm_array-inl.h"
#include "anm/anm_blender.h"
#include "anm/anm_control.h"
#include "anm/anm_extra_truck.h"
#include "anm/anm_factory.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_res_asm.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_skeleton.h"
#include "anm/anm_util.h"

namespace anm {

AsmBlender::AsmBlender() : m_pBlender(nullptr), unknown20(false) {}

AsmBlender::~AsmBlender() {}

void AsmBlender::setup(const ResASM &resAsm, mm::mtl::IAllocator &allocator) { m_pBlender = Factory::createBlender(resAsm.m_pSkeleton, &allocator); }

void AsmBlender::cleanup() {
  unknown001(m_pBlender);
  mm::mtl::IntrusiveList<AsmClip>::iterator it = unknown08.begin();
  while (it != unknown08.end()) {
    it = unknown08.erase(it);
  }
  unknown20 = false;
}

void AsmBlender::sampleTrucks(u32 count, QsTransform *transforms) {
  if (m_pBlender != nullptr && !unknown20) {
    m_pBlender->sampleTrucks(count, transforms);
  }
  unknown002();
}

void AsmBlender::sampleTrucksMS(u32 count, QsTransform *transforms) {
  if (m_pBlender != nullptr && !unknown20) {
    m_pBlender->sampleTrucksMS(count, transforms);
  }
  unknown002();
}

void AsmBlender::sampleExtraTrucks(u16 slot, u32 count, f32 *values) {
  if (m_pBlender == nullptr) {
    return;
  }
  m_pBlender->sampleExtraTrucks(slot, count, values);
  Util::clampLimitExtraTruck(m_pBlender->unknown40->unknown50[slot], count, values);
}

bool AsmBlender::addClip(AsmClip &clip) {
  if (clip.unknown10 == nullptr || !m_pBlender->addControl(clip.unknown10)) {
    return false;
  }
  unknown08.push_back(&clip);
  unknown20 = false;
  return true;
}

void AsmBlender::removeClip(AsmClip &clip) {
  if (clip.unknown10 != nullptr && m_pBlender->removeControl(clip.unknown10)) {
    unknown08.erase(&clip);
  }
  unknown20 = false;
}

AsmClip::AsmClip() : unknown10(nullptr), unknown18(nullptr) {}

AsmClip::~AsmClip() { destroyControl(); }

void AsmClip::destroyControl() {
  if (unknown10 != nullptr) {
    unknown10->release();
    unknown10 = nullptr;
  }
  unknown18 = nullptr;
}

void AsmClip::createControl(const ResClipData &resClipData, mm::mtl::IAllocator &allocator) {
  unknown10 = Factory::createControl(resClipData.m_pBinding, &allocator);
  unknown18 = &resClipData;
}

void AsmClip::setLocalTime(f32 time) {
  if (unknown10 != nullptr) {
    unknown10->setLocalTime(time);
  }
}

f32 AsmClip::getLocalTime() const {
  if (unknown10 != nullptr) {
    return unknown10->unknown48;
  }
  return 0.0f;
}

void AsmClip::setSpeed(f32 speed) {
  if (unknown10 != nullptr) {
    unknown10->unknown50 = unknown18->unknown00->speed * speed;
  }
}

void AsmClip::setWeight(f32 weight) {
  if (unknown10 != nullptr) {
    unknown10->unknown4c = unknown18->unknown00->weight * weight;
  }
}

} // namespace anm
