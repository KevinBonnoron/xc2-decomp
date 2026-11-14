#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class MovieManager : public IManager, public mm::mtl::Singleton<MovieManager> {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: open flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: loaded flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: play flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: disp request flag; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: auto stop flag; original name unknown.
    FLAG_UNKNOWN_5 = 1 << 5, // Inferred role: disp wait flag; original name unknown.
    FLAG_UNKNOWN_6 = 1 << 6, // Inferred role: close wait flag; original name unknown.
    FLAG_UNKNOWN_7 = 1 << 7, // Inferred role: capture flag; original name unknown.
    FLAG_UNKNOWN_8 = 1 << 8, // Inferred role: script flag; original name unknown.
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
  static bool makePath(mm::mtl::FixStr<256> &path, const char *name);
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
  u32 unknown10;                   // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<256> unknown14;  // Inferred role: preload path; original member name unknown.
  bool unknown118;                 // Inferred role: is preload full size; original member name unknown.
  mm::mtl::FixStr<256> unknown11c; // Inferred role: play path; original member name unknown.
  s64 unknown220;                  // Inferred role: unused; original member name unknown.
  int unknown228;                  // Inferred role: disp timer; original member name unknown.
  int unknown22c;                  // Inferred role: close timer; original member name unknown.
};

static_assert(sizeof(MovieManager) == 0x230, "");

} // namespace event
