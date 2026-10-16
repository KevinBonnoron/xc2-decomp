#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace event {

class BgmManager : public IManager, public mm::mtl::NoncopyableBase {
public:
  static constexpr f32 TO_FR = 30.0f;
  static constexpr f32 TO_SEC = 1.0f / 30.0f;

  enum {
    FLAG_HAND_OVER = 1 << 0,
    FLAG_PLAY = 1 << 1,
    FLAG_DELAY = 1 << 2,
    FLAG_ENDLESS = 1 << 3,
    FLAG_KEEP = 1 << 4,
    FLAG_STOP = 1 << 5,
    FLAG_SYNC = 1 << 6,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  BgmManager();
  virtual ~BgmManager() {}
  void clear();
  void update();
  void stop();
  void render();
  void setHandOver(bool isHandOver);
  void playDefaultBgm(f32 fadeFrame);
  void play(const char *name, f32 playFrame, f32 volume, f32 volumeFrame, f32 fadeFrame, f32 delayFrame, f32 fadeOutFrame, f32 startFrame,
            bool isKeep, f32 overTimeFrame);
  void changeVolume(f32 volume, f32 frame);
  void setSyncFrame(f32 frame);
  f32 getStartedTotalFrame() const;
  void cancelOverTime() const;
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      flags |= flag;
    } else {
      flags &= ~flag;
    }
  }

  u32 flags;
  u32 dispFlags;
  mm::mtl::FixStr<64> mName;
  f32 mVolume;
  f32 mVolumeFrame;
  f32 mFadeFrame;
  f32 mStartFrame;
  f32 mDelayFrame;
  f32 mFadeOutFrame;
  f32 mOverTimeFrame;
  f32 mStartedTotalFrame;
  f32 mPlayFrame;
  f32 mSyncFrame;
  s32 mSyncWait;
};

static_assert(sizeof(BgmManager) == 0x88, "");

} // namespace event
