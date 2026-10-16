#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_PAUSE_HANDLE;
}

namespace event {

enum ACC_TYPE {
  ACC_TYPE_NONE,
  ACC_TYPE_NORMAL,
};

struct FrameInfo {
  f32 frame;
  f32 delta;
  f32 pauseDelta;
  f32 streamDelta;
  f32 accFrame;
};

class FrameManager : public IManager, public mm::mtl::Singleton<FrameManager> {
public:
  static constexpr u32 KEY_FRAME_COUNT = 512;
  static constexpr f32 DEFAULT_MAX_FRAME = 1000.0f;

  enum PAUSE_TYPE {
    PAUSE_TYPE_WAIT = 0,
    PAUSE_TYPE_SKIP = 1,
    PAUSE_TYPE_SELECT = 2,
    PAUSE_TYPE_QUEST = 3,
    PAUSE_TYPE_COMMON_UI = 4,
    PAUSE_TYPE_FIELD_SKILL = 5,
    PAUSE_TYPE_SHOP_UI = 6,
    PAUSE_TYPE_PAYOFF_UI = 7,
    PAUSE_TYPE_REWARD_UI = 8,
    PAUSE_TYPE_RAND = 9,
    PAUSE_TYPE_HOMURA_HIKARI_UI = 11,
    PAUSE_TYPE_MINIGAME = 12,
    PAUSE_TYPE_NEW_GAME_WAIT = 13,
    PAUSE_TYPE_COUNT = 17,
    PAUSE_TYPE_ALL = PAUSE_TYPE_COUNT,
  };

  enum {
    FLAG_STREAM_MODE = 1 << 0,
    FLAG_CS_SND_ACC_ENABLE = 1 << 1,
    FLAG_CPU_ACC_ENABLE = 1 << 2,
    FLAG_LOCK_FRAME = 1 << 3,
    FLAG_MAKE_CAPTURE_FRAME = 1 << 4,
    FLAG_CAPTURE_FRAME_SET = 1 << 5,
    FLAG_CAPTURE_FRAME = 1 << 6,
    FLAG_REQUEST_FRAME = 1 << 7,
    FLAG_PAGE_START = 1 << 8,
    FLAG_WAITING = 1 << 9,
    FLAG_BACKUP_FRAME = 1 << 10,
    FLAG_RESTORE_FRAME = 1 << 11,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
    DISP_FLAG_SYNCFRAME = 1 << 1,
    DISP_FLAG_PAGE = 1 << 2,
    DISP_FLAG_USE_SKIP = 1 << 3,
    DISP_FLAG_USE_STOP3D = 1 << 4,
    DISP_FLAG_USE_ACC_PRINT = 1 << 5,
  };

  static constexpr u32 PAUSE_PRESERVED_BITS = 1 << 14;

  struct KeyFrame {
    f32 frame;
    bool isCut;
  };

  f32 getFrame() const;
  bool isPause(PAUSE_TYPE type) const;
  const FrameInfo &frameInfo();
  f32 getTotalFrame() const;
  void pause(PAUSE_TYPE type, bool isPause);
  void requestFrame(f32 frame);
  void setLockFrame(bool isLock, f32 frame);
  FrameManager();
  virtual ~FrameManager() {}
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

  void clearPage() {
    mMaxFrame = DEFAULT_MAX_FRAME;
    mKomaCount = -1;
    mPageName = "";
    mPageID = 0;
    frame = 0.0f;
    mNextFrame = 0.0f;
    mReachedFrame = 0.0f;
    mSkipAbleFrame = 0.0f;
    mKeyFrames.clear();
    mAccFrame = 0.0f;
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
  f32 mNextFrame;
  f32 mBackupFrame;
  f32 mReachedFrame;
  f32 mMaxFrame;
  f32 mLockFrame;
  f32 mCaptureFrame;
  f32 mRequestFrame;
  f32 mSkipAbleFrame;
  ACC_TYPE mAccType;
  f32 mAccFrame;
  u8 _164[0x168 - 0x164];
  mm::mtl::FixedVector<KeyFrame, KEY_FRAME_COUNT> mKeyFrames;
  FrameInfo mFrameInfo;
  int mPageDispCount;
  int mKomaCount;
  PAUSE_TYPE mKomaType;
};

static_assert(sizeof(FrameManager) == 0x1190, "");

} // namespace event
