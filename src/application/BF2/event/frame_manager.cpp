#include "event/frame_manager.h"

#include <stddef.h>

#include "event/manager.h"

namespace event {

FrameManager::FrameManager()
    : flags(0), mPauseBits(0), frame(0.0f), mTotalFrame(0.0f), mSkipStartFrame(0.0f), mNextFrame(0.0f), mReachedFrame(0.0f),
      mMaxFrame(DEFAULT_MAX_FRAME), mAccType(ACC_TYPE_NORMAL), mFrameInfo() {
  dispFlags = DISP_FLAG_SYNCFRAME;
  for (u32 i = 0; i < PAUSE_TYPE_COUNT; i++) {
    mPauseHandles[i] = reinterpret_cast<gf::GF_PAUSE_HANDLE *>(-1);
  }
}

void FrameManager::login() {
  mTotalFrame = 0.0f;
  mSkipStartFrame = 0.0f;
}

void FrameManager::tailAlways() {
  if (flags & FLAG_BACKUP_FRAME) {
    f32 frame = mNextFrame;
    flags &= ~FLAG_BACKUP_FRAME;
    mBackupFrame = frame;
    return;
  }
  if (flags & FLAG_RESTORE_FRAME) {
    f32 frame = mBackupFrame;
    flags &= ~FLAG_RESTORE_FRAME;
    mNextFrame = frame;
  }
  this->frame = mNextFrame;
  if (mReachedFrame < this->frame) {
    mReachedFrame = this->frame;
  }
}

void FrameManager::setStreamMode(bool isStreamMode) { setFlag(FLAG_STREAM_MODE, isStreamMode); }

void FrameManager::setCsSndAccEnable(bool isEnable) { setFlag(FLAG_CS_SND_ACC_ENABLE, isEnable); }

void FrameManager::setCpuAccEnable(bool isEnable) { setFlag(FLAG_CPU_ACC_ENABLE, isEnable); }

void FrameManager::setInfomation(const char *pageName, int pageID, f32 maxFrame) {
  bool isMakeCapture = (flags & FLAG_MAKE_CAPTURE_FRAME) != 0;
  mPageName = pageName;
  mPageID = pageID;
  mMaxFrame = __builtin_fmaxf(maxFrame, 0.0f);
  if (isMakeCapture && Manager::get()->getStartPageID() <= pageID) {
    flags |= FLAG_CAPTURE_FRAME_SET;
    mCaptureFrame = mMaxFrame - 1.0f;
  }
}

const char *FrameManager::getPageName() const { return mPageName.c_str(); }

int FrameManager::getPageID() const { return mPageID; }

void FrameManager::pauseClearAll() {
  for (u32 i = 0; i < PAUSE_TYPE_COUNT; i++) {
    pause(static_cast<PAUSE_TYPE>(i), false);
  }
}

void FrameManager::koma(PAUSE_TYPE type) {
  pause(type, false);
  mKomaCount = 1;
  mKomaType = type;
}

void FrameManager::setFrame(f32 frame) {
  frame = frame < mMaxFrame ? frame : mMaxFrame;
  mNextFrame = frame;
  this->frame = frame;
}

f32 FrameManager::getMaxFrame() const { return mMaxFrame; }

void FrameManager::setMakeCaptureFrame(bool isMake) { setFlag(FLAG_MAKE_CAPTURE_FRAME, isMake); }

bool FrameManager::isCaptureFrame() const { return (flags & FLAG_CAPTURE_FRAME) != 0; }

void FrameManager::setSkipAbleFrame(f32 frame) {
  mSkipAbleFrame = frame;
  mTotalFrame = mSkipStartFrame + frame;
}

void FrameManager::addKeyFrame(f32 frame, bool isCut) {
  KeyFrame key;
  key.frame = frame;
  key.isCut = isCut;
  if (!mKeyFrames.empty() && !(mKeyFrames.back().frame < frame)) {
    for (size_t i = 0; i < mKeyFrames.size(); i++) {
      KeyFrame &keyFrame = mKeyFrames[i];
      if (key.frame == keyFrame.frame) {
        if (isCut) {
          keyFrame.isCut = true;
        }
        return;
      }
      if (key.frame < keyFrame.frame) {
        f32 nextFrame = keyFrame.frame;
        bool nextIsCut = keyFrame.isCut;
        keyFrame.frame = key.frame;
        keyFrame.isCut = key.isCut;
        key.frame = nextFrame;
        key.isCut = nextIsCut;
      }
    }
  }
  mKeyFrames.push_back(key);
}

void FrameManager::shiftFrame(f32 frame) {
  if (mKeyFrames.empty()) {
    return;
  }
  if (this->frame < frame) {
    f32 lastFrame = mKeyFrames.back().frame;
    shiftRight(false, lastFrame > frame ? frame : lastFrame);
    dispFlags |= DISP_FLAG_PAGE;
    mPageDispCount = 0;
  } else if (this->frame > frame) {
    shiftLeft(false, frame > 0.0f ? frame : 0.0f);
  }
}

void FrameManager::setAccframe(bool isAcc, ACC_TYPE type) { mAccType = isAcc ? type : ACC_TYPE_NONE; }

ACC_TYPE FrameManager::getAccType() const { return mAccType; }

void FrameManager::queryCutList(mm::mtl::FixedVector<f32, KEY_FRAME_COUNT> &cutList) const {
  cutList.clear();
  for (size_t i = 0; i < mKeyFrames.size(); i++) {
    if (mKeyFrames[i].isCut) {
      cutList.push_back(mKeyFrames[i].frame);
    }
  }
}

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
