#include "event/shake_manager.h"

#include "event/frame_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"

namespace event {

static constexpr f32 IDLE_SHAKE_TIME = -1.0f;

mm::mtl::FixStr<32> ShakeManager::s_names[TYPE_COUNT] = {"TYPE_SS", "TYPE_S", "TYPE_M", "TYPE_L"};

ShakeManager::ShakeManager() : flags(0) {}

void ShakeManager::create() {
  shaker.create();
  idleShakeId = shaker.registerShake("event/cam/cm_cam_noise_idle.eva");
  shakeIds[TYPE_SS] = shaker.registerShake("event/cam/cm_cam_noise_ss.eva");
  shakeIds[TYPE_S] = shaker.registerShake("event/cam/cm_cam_noise_s.eva");
  shakeIds[TYPE_M] = shaker.registerShake("event/cam/cm_cam_noise_m.eva");
  shakeIds[TYPE_L] = shaker.registerShake("event/cam/cm_cam_noise_l.eva");
}

void ShakeManager::destroy() {
  clear();
  shaker.destroy();
  for (u32 i = 0; i < TYPE_COUNT; i++) {
    shakeIds[i] = 0;
  }
  idleShakeId = 0;
}

void ShakeManager::clear() {
  shaker.stop();
  flags = 0;
}

void ShakeManager::update() {
  if ((flags & FLAG_SHAKE) != 0 && !shaker.isPlay()) {
    idle();
  }
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  if (info.streamDelta > 0.0f) {
    shaker.exec(info.delta, info.streamDelta);
  }
}

void ShakeManager::idle() {
  if ((flags & FLAG_IDLE_SHAKE) != 0) {
    shaker.play(idleShakeId, IDLE_SHAKE_TIME, IDLE_SHAKE_TIME, IDLE_SHAKE_TIME);
  } else {
    shaker.stop();
  }
  flags &= ~FLAG_SHAKE;
}

void ShakeManager::tail() { shaker.tail(); }

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
  shaker.play(shakeIds[type], life, fadeIn, fadeOut);
  flags |= FLAG_SHAKE;
}

void ShakeManager::setIdleShake(bool isIdleShake) {
  if (((flags & FLAG_IDLE_SHAKE) != 0) == isIdleShake) {
    return;
  }
  if (isIdleShake) {
    flags |= FLAG_IDLE_SHAKE;
  } else {
    flags &= ~FLAG_IDLE_SHAKE;
  }
  if ((flags & FLAG_SHAKE) == 0) {
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
