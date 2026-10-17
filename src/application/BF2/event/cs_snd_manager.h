#pragma once
#include "event/i_manager.h"
#include "framework/sound/sound_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CsSndManager : public IManager, public mm::mtl::Singleton<CsSndManager> {
public:
  enum {
    FLAG_PRELOAD = 1 << 0,
    FLAG_PLAY = 1 << 1,
    FLAG_PAUSE = 1 << 2,
    FLAG_STALL = 1 << 3,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  CsSndManager();
  virtual ~CsSndManager() {}
  void clear();
  void stop();
  void update();
  void render();
  f32 getPlayFrame() const;
  f32 getTotalFrame() const;
  void preloadAuto(const char *name);
  static void makePath(mm::mtl::FixStr<256> &path, const char *name);
  void preload(const char *path);
  bool isLoading() const;
  void playAuto(const char *name);
  void play(const char *path);
  static u32 playBgm(const char *path, f32 volume, bool isPause);
  bool isPlay() const;
  void pause(bool isPause);
  void setDisp(bool isDisp);
  bool isDisp() const;
  f32 getSyncFrame() const;
  void setSyncFrame(f32 frame);
  f32 getStartedTotalFrame() const;
  void setSyncFrameOffset(f32 offset);
  virtual void OnEventProc(MSG_TYPE type);

private:
  void stopPreload() {
    fw::SoundManager::get()->stopBgm(mPreloadHandle, 1.0f);
    mPreloadHandle = 0;
    mPreloadPath = "";
    flags &= ~FLAG_PRELOAD;
  }

  void stopPlay() {
    fw::SoundManager::get()->stopBgm(mPlayHandle, 1.0f);
    mPlayHandle = 0;
    mPlayPath = "";
    flags &= ~(FLAG_PLAY | FLAG_PAUSE | FLAG_STALL);
  }

  u32 flags;
  u32 dispFlags;
  u32 mPreloadHandle;
  u32 mPlayHandle;
  mm::mtl::FixStr<256> mPreloadPath;
  mm::mtl::FixStr<256> mPlayPath;
  f32 mPrevPlayTime;
  int mStallCount;
  int mRestartCount;
  f32 mStartedTotalFrame;
  u64 mUnused;
  f32 mSyncFrameOffset;
};

static_assert(sizeof(CsSndManager) == 0x248, "");

} // namespace event
