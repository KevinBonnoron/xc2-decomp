#include "event/shake_manager.h"

#include "event/frame_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"

namespace event {

static constexpr f32 IDLE_SHAKE_TIME = -1.0f;

mm::mtl::FixStr<32> ShakeManager::s_names[TYPE_COUNT] = {"TYPE_SS", "TYPE_S", "TYPE_M", "TYPE_L"};

ShakeManager::ShakeManager() : unknown10(0) {}

void ShakeManager::create() {
  unknown18.create();
  unknowncb8 = unknown18.registerShake("event/cam/cm_cam_noise_idle.eva");
  unknownca8[TYPE_SS] = unknown18.registerShake("event/cam/cm_cam_noise_ss.eva");
  unknownca8[TYPE_S] = unknown18.registerShake("event/cam/cm_cam_noise_s.eva");
  unknownca8[TYPE_M] = unknown18.registerShake("event/cam/cm_cam_noise_m.eva");
  unknownca8[TYPE_L] = unknown18.registerShake("event/cam/cm_cam_noise_l.eva");
}

void ShakeManager::destroy() {
  clear();
  unknown18.destroy();
  for (u32 i = 0; i < TYPE_COUNT; i++) {
    unknownca8[i] = 0;
  }
  unknowncb8 = 0;
}

void ShakeManager::clear() {
  unknown18.stop();
  unknown10 = 0;
}

void ShakeManager::update() {
  if ((unknown10 & FLAG_SHAKE) != 0 && !unknown18.isPlay()) {
    idle();
  }
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  if (info.unknown0c > 0.0f) {
    unknown18.exec(info.unknown04, info.unknown0c);
  }
}

void ShakeManager::idle() {
  if ((unknown10 & FLAG_IDLE_SHAKE) != 0) {
    unknown18.play(unknowncb8, IDLE_SHAKE_TIME, IDLE_SHAKE_TIME, IDLE_SHAKE_TIME);
  } else {
    unknown18.stop();
  }
  unknown10 &= ~FLAG_SHAKE;
}

void ShakeManager::tail() { unknown18.tail(); }

void ShakeManager::play(const char *name, f32 life, f32 fadeIn, f32 fadeOut) {
  int type = 0;
  for (; type < TYPE_COUNT; type++) {
    if (__builtin_strcmp(s_names[type].c_str(), name) == 0) {
      break;
    }
  }
  if (type == TYPE_COUNT) {
    return;
  }
  unknown18.play(unknownca8[type], life, fadeIn, fadeOut);
  unknown10 |= FLAG_SHAKE;
}

void ShakeManager::setIdleShake(bool isIdleShake) {
  if (((unknown10 & FLAG_IDLE_SHAKE) != 0) == isIdleShake) {
    return;
  }
  if (isIdleShake) {
    unknown10 |= FLAG_IDLE_SHAKE;
  } else {
    unknown10 &= ~FLAG_IDLE_SHAKE;
  }
  if ((unknown10 & FLAG_SHAKE) == 0) {
    idle();
  }
}

void ShakeManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_TAIL:
    tail();
    break;
  default:
    break;
  }
}

} // namespace event
