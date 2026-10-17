#pragma once
#include <stddef.h>

#include "anm/anm_asm_callback_detector.h"
#include "anm/anm_asm_listener.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "anm/anm_util.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class AsmBlender;
class AsmClip;
class Binding;

f32 rand();

class AsmState : public ReferenceObject {
public:
  AsmState(const ResStateData *pResStateData, mm::mtl::IAllocator &allocator)
      : ReferenceObject(&allocator), m_pResStateData(pResStateData), m_speed(1.0f), m_weight(1.0f), m_loopNum(0), m_loopCount(0) {}
  virtual ~AsmState() {}
  virtual void attach(AsmBlender *blender) = 0;
  virtual void dettach(AsmBlender *blender) = 0;
  virtual void onEnter(AsmListener *listener) = 0;
  virtual void onLeave(AsmListener *listener) = 0;
  virtual void update(f32 deltaTime, AsmListener *listener) = 0;
  virtual void setLocalTime(f32 time) = 0;
  virtual f32 getLocalTime() const = 0;
  virtual void onSetSpeed() = 0;
  virtual void onSetWeight() = 0;
  virtual const AsmClip *getBaseClip() const = 0;

  void setSpeed(f32 speed) {
    m_speed = speed;
    onSetSpeed();
  }

  void initLoopCount() {
    const ResState *resState = m_pResStateData->m_pResState;
    const Binding *binding = m_pResStateData->m_clips[0].m_pBinding;
    m_loopCount = 0;
    if (resState->loopCount != nullptr) {
      m_loopNum = resState->loopCount->min + static_cast<u32>(resState->loopCount->range * rand());
    } else if (binding != nullptr && Util::getPlayMode(*binding) == PLAY_MODE_ONCE) {
      m_loopNum = 1;
    } else {
      m_loopNum = 0;
    }
  }

  void notifyEnter(AsmListener *listener) {
    for (u32 type = 0; type < 5; type++) {
      if (listener != nullptr && !m_pResStateData->m_enterAnnotations[type].empty()) {
        CallBackDetector::execute(*listener, AsmListener::CALLBACK_ENTER, m_pResStateData->m_enterAnnotations[type]);
      }
      const mm::mtl::Vector<ResClipData> &clips = m_pResStateData->m_clips;
      for (u32 i = 0; i < clips.size(); i++) {
        const ResClipData &clip = clips[i];
        if (listener != nullptr && !clip.m_frameAnnotations[type].empty()) {
          CallBackDetector::executeStartFrame(*listener, clip.m_startFrame, clip.m_frameAnnotations[type]);
        }
      }
    }
  }

  void notifyLeave(AsmListener *listener) {
    if (listener == nullptr) {
      return;
    }
    for (u32 type = 0; type < 5; type++) {
      if (!m_pResStateData->m_leaveAnnotations[type].empty()) {
        CallBackDetector::execute(*listener, AsmListener::CALLBACK_LEAVE, m_pResStateData->m_leaveAnnotations[type]);
      }
    }
  }

  const ResStateData *m_pResStateData;
  f32 m_speed;
  f32 m_weight;
  s32 m_loopNum;
  s32 m_loopCount;
};

static_assert(offsetof(AsmState, m_pResStateData) == 0x18, "");
static_assert(sizeof(AsmState) == 0x30, "");

} // namespace anm
