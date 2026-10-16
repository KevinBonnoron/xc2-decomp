#include "event/cpu_manager.h"

namespace event {

CpuManager::CpuManager() : flags(0), frame(0.0f), mStartFrame(0.0f), mPauseFrame(0.0f), mCpuFrame(0.0f) { mTimeCount.start(); }

void CpuManager::init() {
  flags = 0;
  frame = 0.0f;
  mCpuFrame = 0.0f;
}

void CpuManager::end() {
  flags = 0;
  frame = 0.0f;
  mCpuFrame = 0.0f;
}

void CpuManager::update() {
  if (isRunning()) {
    f32 frame = calcCpuFrame() - mStartFrame;
    mCpuFrame = __builtin_fmaxf(frame, 0.0f);
  }
}

f32 CpuManager::calcCpuFrame() const { return static_cast<int>(mTimeCount.getSecLap() * 30.0f); }

void CpuManager::tailAlways() {
  if (isRunning()) {
    frame = mCpuFrame;
  }
}

void CpuManager::start() {
  frame = 0.0f;
  mCpuFrame = 0.0f;
  mStartFrame = calcCpuFrame();
  flags |= FLAG_START;
}

f32 CpuManager::getFrame() const { return frame; }

void CpuManager::pause(bool isPause) {
  if ((flags & FLAG_START) == 0) {
    return;
  }
  bool wasPaused = (flags & (FLAG_PAUSE | FLAG_PAUSE_HOME)) != 0;
  setFlag(FLAG_PAUSE, isPause);
  bool isPaused = (flags & (FLAG_PAUSE | FLAG_PAUSE_HOME)) != 0;
  if (wasPaused != isPaused) {
    f32 frame = calcCpuFrame();
    if (isPaused) {
      mPauseFrame = frame;
    } else {
      f32 startFrame = mStartFrame + (frame - mPauseFrame);
      mStartFrame = __builtin_fmaxf(startFrame, 0.0f);
    }
  }
}

void CpuManager::pauseHome(bool isPause) {
  if ((flags & FLAG_START) == 0) {
    return;
  }
  bool wasPaused = (flags & (FLAG_PAUSE | FLAG_PAUSE_HOME)) != 0;
  setFlag(FLAG_PAUSE_HOME, isPause);
  bool isPaused = (flags & (FLAG_PAUSE | FLAG_PAUSE_HOME)) != 0;
  if (wasPaused != isPaused) {
    f32 frame = calcCpuFrame();
    if (isPaused) {
      mPauseFrame = frame;
    } else {
      f32 startFrame = mStartFrame + (frame - this->frame);
      mStartFrame = __builtin_fmaxf(startFrame, 0.0f);
    }
  }
}

void CpuManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    init();
    break;
  case MSG_TYPE_CLEAR:
    end();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_TAIL_POST:
    tailAlways();
    break;
  default:
    break;
  }
}

} // namespace event
