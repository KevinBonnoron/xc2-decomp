#include "event/frame_manager.h"

namespace event {

void FrameManager::login() {
  mTotalFrame = 0.0f;
  mSkipStartFrame = 0.0f;
}

void FrameManager::setStreamMode(bool isStreamMode) { setFlag(FLAG_STREAM_MODE, isStreamMode); }

void FrameManager::setCsSndAccEnable(bool isEnable) { setFlag(FLAG_CS_SND_ACC_ENABLE, isEnable); }

void FrameManager::setCpuAccEnable(bool isEnable) { setFlag(FLAG_CPU_ACC_ENABLE, isEnable); }

const char *FrameManager::getPageName() const { return mPageName.c_str(); }

int FrameManager::getPageID() const { return mPageID; }

void FrameManager::setFrame(f32 frame) {
  frame = frame < mMaxFrame ? frame : mMaxFrame;
  mPrevFrame = frame;
  this->frame = frame;
}

f32 FrameManager::getMaxFrame() const { return mMaxFrame; }

void FrameManager::setMakeCaptureFrame(bool isMake) { setFlag(FLAG_MAKE_CAPTURE_FRAME, isMake); }

bool FrameManager::isCaptureFrame() const { return (flags & FLAG_CAPTURE_FRAME) != 0; }

void FrameManager::setSkipAbleFrame(f32 frame) {
  mSkipAbleFrame = frame;
  mTotalFrame = mSkipStartFrame + frame;
}

void FrameManager::setAccframe(bool isAcc, ACC_TYPE type) { mAccType = isAcc ? type : ACC_TYPE_NONE; }

ACC_TYPE FrameManager::getAccType() const { return mAccType; }

void FrameManager::setDisp(bool isDisp) { setDispFlag(DISP_FLAG_DISP, isDisp); }

bool FrameManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

void FrameManager::setUseSkip(bool isUse) { setDispFlag(DISP_FLAG_USE_SKIP, isUse); }

void FrameManager::setUseStop3D(bool isUse) { setDispFlag(DISP_FLAG_USE_STOP3D, isUse); }

void FrameManager::setUseAccPrint(bool isUse) { setDispFlag(DISP_FLAG_USE_ACC_PRINT, isUse); }

bool FrameManager::isUseAccPrint() const { return (dispFlags & DISP_FLAG_USE_ACC_PRINT) != 0; }

void FrameManager::setSyncframe(bool isSync) { setDispFlag(DISP_FLAG_SYNCFRAME, isSync); }

bool FrameManager::isSyncframe() const { return (dispFlags & DISP_FLAG_SYNCFRAME) != 0; }

bool FrameManager::isWaiting() const { return (flags & FLAG_WAITING) != 0; }

} // namespace event
