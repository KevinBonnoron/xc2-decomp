#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace gf {
struct GF_PAUSE_HANDLE;
}

namespace event {

enum ACC_TYPE {
  ACC_TYPE_NONE,
  ACC_TYPE_NORMAL,
};

class FrameManager : public IManager, public mm::mtl::NoncopyableBase {
public:
  static constexpr u32 KEY_FRAME_COUNT = 512;
  static constexpr f32 DEFAULT_MAX_FRAME = 1000.0f;

  enum PAUSE_TYPE {
    PAUSE_TYPE_COUNT = 17,
    PAUSE_TYPE_ALL = PAUSE_TYPE_COUNT,
  };

  enum {
    FLAG_STREAM_MODE = 1 << 0,
    FLAG_CS_SND_ACC_ENABLE = 1 << 1,
    FLAG_CPU_ACC_ENABLE = 1 << 2,
    FLAG_LOCK_FRAME = 1 << 3,
    FLAG_MAKE_CAPTURE_FRAME = 1 << 4,
    FLAG_CAPTURE_FRAME = 1 << 6,
    FLAG_REQUEST_FRAME = 1 << 7,
    FLAG_WAITING = 1 << 9,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
    DISP_FLAG_SYNCFRAME = 1 << 1,
    DISP_FLAG_PAGE = 1 << 2,
    DISP_FLAG_USE_SKIP = 1 << 3,
    DISP_FLAG_USE_STOP3D = 1 << 4,
    DISP_FLAG_USE_ACC_PRINT = 1 << 5,
  };

  struct KeyFrame {
    f32 frame;
    bool isCut;
  };

  FrameManager();
  virtual ~FrameManager() {}
  f32 getFrame() const { return frame; }
  bool isPause(PAUSE_TYPE type) const { return (mPauseBits & (type == PAUSE_TYPE_ALL ? ~0u : 1u << type)) != 0; }
  f32 getTotalFrame() const { return mTotalFrame; }
  void requestFrame(f32 frame) {
    flags |= FLAG_REQUEST_FRAME;
    mRequestFrame = frame;
  }
  void setLockFrame(bool isLock, f32 frame) {
    setFlag(FLAG_LOCK_FRAME, isLock);
    mLockFrame = frame;
  }
  void login();
  void init();
  void end();
  void initPage();
  void update();
  void render();
  void tail();
  void tailAlways();
  void setStreamMode(bool isStreamMode);
  void setCsSndAccEnable(bool isEnable);
  void setCpuAccEnable(bool isEnable);
  void setInfomation(const char *pageName, int pageID, f32 maxFrame);
  const char *getPageName() const;
  int getPageID() const;
  void pauseClearAll();
  void koma(PAUSE_TYPE type);
  void setFrame(f32 frame);
  f32 getMaxFrame() const;
  void setMakeCaptureFrame(bool isMake);
  bool isCaptureFrame() const;
  void setSkipAbleFrame(f32 frame);
  void addKeyFrame(f32 frame, bool isCut);
  void shiftLeft(bool isCut, f32 frame);
  void shiftRight(bool isCut, f32 frame);
  void shiftFrame(f32 frame);
  void setAccframe(bool isAcc, ACC_TYPE type);
  ACC_TYPE getAccType() const;
  void queryCutList(mm::mtl::FixedVector<f32, KEY_FRAME_COUNT> &cutList) const;
  void setDisp(bool isDisp);
  bool isDisp() const;
  void setUseSkip(bool isUse);
  void setUseStop3D(bool isUse);
  void setUseAccPrint(bool isUse);
  bool isUseAccPrint() const;
  void setSyncframe(bool isSync);
  bool isSyncframe() const;
  bool isWaiting() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      flags |= flag;
    } else {
      flags &= ~flag;
    }
  }

  void setDispFlag(u32 flag, bool isSet) {
    if (isSet) {
      dispFlags |= flag;
    } else {
      dispFlags &= ~flag;
    }
  }

  u32 flags;
  u32 dispFlags;
  u32 mPauseBits;
  gf::GF_PAUSE_HANDLE *mPauseHandles[PAUSE_TYPE_COUNT];
  mm::mtl::FixStr<128> mPageName;
  int mPageID;
  f32 frame;
  f32 mTotalFrame;
  f32 mSkipStartFrame;
  f32 mPrevFrame;
  u8 _140[0x144 - 0x140];
  u32 mWaitCount;
  f32 mMaxFrame;
  f32 mLockFrame;
  u8 _150[0x154 - 0x150];
  f32 mRequestFrame;
  f32 mSkipAbleFrame;
  ACC_TYPE mAccType;
  u32 mKomaCount;
  mm::mtl::FixedVector<KeyFrame, KEY_FRAME_COUNT> mKeyFrames;
  u64 mCaptureTime;
  u64 mCaptureStartTime;
  u32 mCaptureCount;
  u8 _1184[0x1188 - 0x1184];
  int mNextPageID;
};

static_assert(sizeof(FrameManager) == 0x1190, "");

} // namespace event
