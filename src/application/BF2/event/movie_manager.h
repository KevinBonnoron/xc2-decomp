#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class MovieManager : public IManager, public mm::mtl::Singleton<MovieManager> {
public:
  enum {
    FLAG_OPEN = 1 << 0,
    FLAG_LOADED = 1 << 1,
    FLAG_PLAY = 1 << 2,
    FLAG_DISP_REQUEST = 1 << 3,
    FLAG_AUTO_STOP = 1 << 4,
    FLAG_DISP_WAIT = 1 << 5,
    FLAG_CLOSE_WAIT = 1 << 6,
    FLAG_CAPTURE = 1 << 7,
    FLAG_SCRIPT = 1 << 8,
  };

  MovieManager();
  virtual ~MovieManager() {}
  void clear();
  void close();
  void captureScreen(bool isCapture);
  void update();
  void stop();
  void dispOff();
  void render();
  void preloadAuto(const char *name, bool isFullSize);
  static void makePath(mm::mtl::FixStr<256> &path, const char *name);
  void preload(const char *path, bool isFullSize);
  static bool isSame(const char *path, const char *otherPath);
  bool isLoading() const;
  void playAuto(const char *name, bool isFullSize, bool isAutoStop);
  void play(const char *path, bool isFullSize, bool isAutoStop);
  void dispOn();
  void setScriptFlag(bool isScript);
  bool isLoadedAuto(const char *name, bool isFullSize) const;
  bool isLoaded(const char *path, bool isFullSize) const;
  void pause(bool isPause);
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 flags;
  mm::mtl::FixStr<256> mPreloadPath;
  bool mIsPreloadFullSize;
  mm::mtl::FixStr<256> mPlayPath;
  s64 mUnused;
  int mDispTimer;
  int mCloseTimer;
};

static_assert(sizeof(MovieManager) == 0x230, "");

} // namespace event
