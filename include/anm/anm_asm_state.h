#pragma once
#include <stddef.h>

#include "anm/anm_asm_callback_detector.h"
#include "anm/anm_asm_listener.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "anm/anm_util.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/mt_rand.h"
#include "mm_mtl/vector.h"
#include "nn/os.h"
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

inline f32 rand() {
  static mm::mtl::MTRand sRand(nn::os::GetSystemTick().GetInt64Value());
  return sRand.generate() * (1.0 / 4294967296.0);
}

class AsmState : public ReferenceObject {
public:
  AsmState(const ResStateData *pResStateData, mm::mtl::IAllocator &allocator) : ReferenceObject(&allocator), unknown18(pResStateData), unknown20(1.0f), unknown24(1.0f), unknown28(0), unknown2c(0) {}
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
    unknown20 = speed;
    onSetSpeed();
  }

  void updateLoopCount(bool isEnd) {
    if (unknown28 <= 0) {
      if (unknown28 != 0 || unknown2c != 0 || !isEnd) {
        return;
      }
    } else if (!isEnd) {
      return;
    }
    unknown2c++;
  }

  void initLoopCount() {
    const ResState *resState = unknown18->unknown00;
    const Binding *binding = unknown18->unknown08[0].m_pBinding;
    unknown2c = 0;
    if (resState->loopCount != nullptr) {
      unknown28 = resState->loopCount->min + static_cast<u32>(resState->loopCount->range * rand());
    } else if (binding != nullptr && Util::getPlayMode(*binding) == PLAY_MODE_ONCE) {
      unknown28 = 1;
    } else {
      unknown28 = 0;
    }
  }

  void notifyEnter(AsmListener *listener) {
    for (u32 type = 0; type < 5; type++) {
      if (listener != nullptr && !unknown18->unknown50[type].empty()) {
        CallBackDetector::execute(*listener, AsmListener::CALLBACK_ENTER, unknown18->unknown50[type]);
      }
      const mm::mtl::Vector<ResClipData> &clips = unknown18->unknown08;
      for (u32 i = 0; i < clips.size(); i++) {
        const ResClipData &clip = clips[i];
        if (listener != nullptr && !clip.unknown18[type].empty()) {
          CallBackDetector::executeStartFrame(*listener, clip.unknown10, clip.unknown18[type]);
        }
      }
    }
  }

  void notifyLeave(AsmListener *listener) {
    if (listener == nullptr) {
      return;
    }
    for (u32 type = 0; type < 5; type++) {
      if (!unknown18->unknown118[type].empty()) {
        CallBackDetector::execute(*listener, AsmListener::CALLBACK_LEAVE, unknown18->unknown118[type]);
      }
    }
  }

  const ResStateData *unknown18; // Inferred role: p res state data; original member name unknown.
  f32 unknown20;                 // Inferred role: speed; original member name unknown.
  f32 unknown24;                 // Inferred role: weight; original member name unknown.
  s32 unknown28;                 // Inferred role: loop num; original member name unknown.
  s32 unknown2c;                 // Inferred role: loop count; original member name unknown.
};

static_assert(offsetof(AsmState, unknown18) == 0x18, "");
static_assert(sizeof(AsmState) == 0x30, "");

} // namespace anm
