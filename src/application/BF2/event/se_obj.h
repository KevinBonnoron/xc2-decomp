#pragma once
#include "event/anm_f32.h"
#include "event/curve.h"
#include "gf/sound/gf_sound.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class SeObj {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: play flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: end flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: pause flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: life flag; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: fade in flag; original name unknown.
    FLAG_UNKNOWN_5 = 1 << 5, // Inferred role: fade out flag; original name unknown.
    FLAG_UNKNOWN_6 = 1 << 6, // Inferred role: volume anm flag; original name unknown.
    FLAG_UNKNOWN_7 = 1 << 7, // Inferred role: pan anm flag; original name unknown.
    FLAG_UNKNOWN_8 = 1 << 8, // Inferred role: pan flag; original name unknown.
  };

  SeObj();
  virtual ~SeObj();
  void clear();
  void stop();
  void exec(f32 delta);
  void draw(int index, int x, int y);
  void play(const char *name, f32 life, f32 fadeIn, f32 fadeOut, f32 volume);
  void changeVolume(f32 volume, f32 frame);
  void pan(f32 pan, f32 frame, CV_TYPE cv);
  void pause(bool isPause);
  bool isPlay() const { return (unknown08 & FLAG_UNKNOWN_0) != 0; }
  bool isEnd() const { return (unknown08 & FLAG_UNKNOWN_1) != 0; }

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown08 |= flag;
    } else {
      unknown08 &= ~flag;
    }
  }

  u32 unknown08;                 // Inferred role: flags; original member name unknown.
  gf::SoundHandle unknown0c;     // Inferred role: handle; original member name unknown.
  mm::mtl::FixStr<64> unknown14; // Inferred role: name; original member name unknown.
  f32 unknown58;                 // Inferred role: play frame; original member name unknown.
  f32 unknown5c;                 // Inferred role: life; original member name unknown.
  f32 unknown60;                 // Inferred role: fade in; original member name unknown.
  f32 unknown64;                 // Inferred role: fade out; original member name unknown.
  f32 unknown68;                 // Inferred role: volume; original member name unknown.
  AnmF32 unknown70;              // Inferred role: volume anm; original member name unknown.
  f32 unknown180;                // Inferred role: pan value; original member name unknown.
  AnmF32 unknown188;             // Inferred role: pan anm; original member name unknown.
};

static_assert(sizeof(SeObj) == 0x298, "");

} // namespace event
