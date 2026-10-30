#include "event/cam_motion.h"

#include "event/extend.h"
#include "event/frame_manager.h"
#include "event/motstm_manager.h"
#include "event/res_manager.h"
#include "event/skip_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

CamMotion::CamMotion(bool isFocal, bool isStreamMode) : CamBase(isFocal), unknown48(nullptr), unknown50(nullptr) { unknown40 = isStreamMode; }

CamMotion::~CamMotion() { stop(); }

void CamMotion::stop() {
  unknown60.stop();
  unknowna0.stop();
  if (unknown40 & FLAG_STREAM_MODE) {
    if (unknown48 != nullptr) {
      mm::mtl::Singleton<MotstmManager>::getPtr()->free(unknown48);
    }
    if (unknown50 != nullptr) {
      mm::mtl::Singleton<MotstmManager>::getPtr()->free(unknown50);
    }
  }
  unknown48 = nullptr;
  unknown50 = nullptr;
  unknown40 &= ~(FLAG_PLAY_EVA | FLAG_PLAY_EFF);
}

void CamMotion::play(const char *name, const mm::Vec3 &offset) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  stop();
  if (!(unknown40 & FLAG_STREAM_MODE)) {
    unknown48 = mm::mtl::Singleton<ResManager>::getPtr()->adr(mm::mtl::Singleton<Extend>::getPtr()->eva(name), nullptr);
  } else {
    unknown48 = mm::mtl::Singleton<MotstmManager>::getPtr()->adr(mm::mtl::Singleton<Extend>::getPtr()->eva(name), nullptr);
  }
  if (unknown48 != nullptr) {
    const char *effectName = mm::mtl::Singleton<Extend>::getPtr()->replaceString(name, "event", "effect");
    if (!(unknown40 & FLAG_STREAM_MODE)) {
      unknown50 = mm::mtl::Singleton<ResManager>::getPtr()->adr(mm::mtl::Singleton<Extend>::getPtr()->effeva(effectName), nullptr);
    } else {
      unknown50 = mm::mtl::Singleton<MotstmManager>::getPtr()->adr(mm::mtl::Singleton<Extend>::getPtr()->effeva(effectName), nullptr);
    }
    unknown60.play(this, unknown48, offset);
    unknown40 |= FLAG_PLAY_EVA;
    if (unknown50 != nullptr) {
      unknowna0.play(unknown50);
      unknown40 |= FLAG_PLAY_EFF;
    }
  }
}

void CamMotion::update(const FrameInfo &info) {
  if (unknown40 & FLAG_PLAY_EVA) {
    unknown60.update(info.unknown0c);
  }
  if (unknown40 & FLAG_PLAY_EFF) {
    unknowna0.update(info.unknown0c);
  }
}

} // namespace event
