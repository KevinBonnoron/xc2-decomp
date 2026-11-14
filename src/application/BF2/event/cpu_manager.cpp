#include "event/cpu_manager.h"

namespace event {

CpuManager::CpuManager() : unknown10(0), m_frame(0.0f), unknown18(0.0f), unknown1c(0.0f), unknown20(0.0f) { unknown28.start(); }

void CpuManager::init() {
  unknown10 = 0;
  m_frame = 0.0f;
  unknown20 = 0.0f;
}

void CpuManager::end() {
  unknown10 = 0;
  m_frame = 0.0f;
  unknown20 = 0.0f;
}

void CpuManager::update() {
  if (isRunning()) {
    f32 frame = calcCpuFrame() - unknown18;
    unknown20 = __builtin_fmaxf(frame, 0.0f);
  }
}

f32 CpuManager::calcCpuFrame() const { return static_cast<int>(unknown28.getSecLap() * 30.0f); }

void CpuManager::tailAlways() {
  if (isRunning()) {
    m_frame = unknown20;
  }
}

void CpuManager::start() {
  m_frame = 0.0f;
  unknown20 = 0.0f;
  unknown18 = calcCpuFrame();
  unknown10 |= FLAG_UNKNOWN_0;
}

f32 CpuManager::getFrame() const { return m_frame; }

void CpuManager::pause(bool isPause) {
  if ((unknown10 & FLAG_UNKNOWN_0) == 0) {
    return;
  }
  bool wasPaused = (unknown10 & (FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2)) != 0;
  setFlag(FLAG_UNKNOWN_1, isPause);
  bool isPaused = (unknown10 & (FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2)) != 0;
  if (wasPaused != isPaused) {
    f32 frame = calcCpuFrame();
    if (isPaused) {
      unknown1c = frame;
    } else {
      f32 startFrame = unknown18 + (frame - unknown1c);
      unknown18 = __builtin_fmaxf(startFrame, 0.0f);
    }
  }
}

void CpuManager::pauseHome(bool isPause) {
  if ((unknown10 & FLAG_UNKNOWN_0) == 0) {
    return;
  }
  bool wasPaused = (unknown10 & (FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2)) != 0;
  setFlag(FLAG_UNKNOWN_2, isPause);
  bool isPaused = (unknown10 & (FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2)) != 0;
  if (wasPaused != isPaused) {
    f32 frame = calcCpuFrame();
    if (isPaused) {
      unknown1c = frame;
    } else {
      f32 startFrame = unknown18 + (frame - this->m_frame);
      unknown18 = __builtin_fmaxf(startFrame, 0.0f);
    }
  }
}

void CpuManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
    init();
    break;
  case MSG_TYPE_UNKNOWN_12:
    end();
    break;
  case MSG_TYPE_UNKNOWN_14:
    update();
    break;
  case MSG_TYPE_UNKNOWN_19:
    tailAlways();
    break;
  default:
    break;
  }
}

} // namespace event
