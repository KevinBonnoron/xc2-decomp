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
  static const f32 TO_SEC;                 // Name given by the xc2 symbol _ZN5event11VoicePlayer6TO_SECE.
  static const f32 TO_FR;                  // Name given by the xc2 symbol _ZN5event11VoicePlayer5TO_FRE.
  static constexpr u32 KEY_UNKNOWN_8 = 8;  // Inferred role: key count; original name unknown.
  static constexpr u32 PLAY_UNKNOWN_4 = 4; // Inferred role: play count; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: delay flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: started flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: start failed flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: pause flag; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: multiple mode flag; original name unknown.
  };

  struct Key {
    Key(f32 frame, const char *path) : unknown00(frame), unknown04(path) {}

    f32 unknown00;                 // Inferred role: frame; original member name unknown.
    mm::mtl::FixStr<64> unknown04; // Inferred role: path; original member name unknown.
  };

  struct Play {
    Play(u32 handle, const char *path) : unknown00(handle), unknown04(path), unknown48(-1.0f), unknown4c(0), unknown50(0) {}

    u32 unknown00;                 // Inferred role: handle; original member name unknown.
    mm::mtl::FixStr<64> unknown04; // Inferred role: path; original member name unknown.
    f32 unknown48;                 // Inferred role: play time; original member name unknown.
    int unknown4c;                 // Inferred role: stall count; original member name unknown.
    int unknown50;                 // Inferred role: retake count; original member name unknown.
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
  u32 unknown08;                                         // Inferred role: flags; original member name unknown.
  mm::mtl::FixedList<Key, KEY_UNKNOWN_8> unknown0c;      // Inferred role: keys; original member name unknown.
  mm::mtl::FixedVector<Play, PLAY_UNKNOWN_4> unknown2d0; // Inferred role: plays; original member name unknown.
  mm::mtl::FixStr<64> unknown428;                        // Inferred role: waiting path; original member name unknown.
  u32 unknown46c;                                        // Inferred role: waiting handle; original member name unknown.
  f32 unknown470;                                        // Inferred role: delay; original member name unknown.
  mm::mtl::FixStr<64> unknown474;                        // Inferred role: path; original member name unknown.
  u32 unknown4b8;                                        // Inferred role: handle; original member name unknown.
  IVoiceEvent *unknown4c0;                               // Inferred role: event; original member name unknown.
};

static_assert(sizeof(VoicePlayer) == 0x4c8, "");

} // namespace event
