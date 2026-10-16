#pragma once
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class IVoiceEvent {
public:
  virtual void OnVoicePlay(const char *path, bool isPlaying) = 0;
};

class VoicePlayer {
public:
  static const f32 TO_SEC;
  static const f32 TO_FR;
  static constexpr u32 KEY_COUNT = 8;
  static constexpr u32 PLAY_COUNT = 4;

  enum {
    FLAG_DELAY = 1 << 0,
    FLAG_STARTED = 1 << 1,
    FLAG_START_FAILED = 1 << 2,
    FLAG_PAUSE = 1 << 3,
    FLAG_MULTIPLE_MODE = 1 << 4,
  };

  struct Key {
    Key(f32 frame, const char *path) : frame(frame), path(path) {}

    f32 frame;
    mm::mtl::FixStr<64> path;
  };

  struct Play {
    Play(u32 handle, const char *path) : handle(handle), path(path), playTime(-1.0f), stallCount(0), retakeCount(0) {}

    u32 handle;
    mm::mtl::FixStr<64> path;
    f32 playTime;
    int stallCount;
    int retakeCount;
  };

  VoicePlayer();
  virtual ~VoicePlayer() {}
  void clear();
  void stop(f32 frame);
  void clearPreload();
  void update();
  void stopWaiting();
  void draw();
  f32 getPlayFrame() const;
  f32 getTotalFrame() const;
  void setMultipleMode(bool isMultipleMode);
  void preload(f32 frame, const char *path);
  bool play(const char *path, f32 delay, IVoiceEvent *event);
  void clr();
  void pause(bool isPause);
  void startWaiting(const char *path);
  bool isPlay() const;
  const char *getPath() const;

private:
  u32 flags;
  mm::mtl::FixedList<Key, KEY_COUNT> keys;
  mm::mtl::FixedVector<Play, PLAY_COUNT> plays;
  mm::mtl::FixStr<64> waitingPath;
  u32 waitingHandle;
  f32 delay;
  mm::mtl::FixStr<64> path;
  u32 handle;
  IVoiceEvent *event;
};

static_assert(sizeof(VoicePlayer) == 0x4c8, "");

} // namespace event
