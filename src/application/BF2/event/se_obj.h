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
    FLAG_PLAY = 1 << 0,
    FLAG_END = 1 << 1,
    FLAG_PAUSE = 1 << 2,
    FLAG_LIFE = 1 << 3,
    FLAG_FADE_IN = 1 << 4,
    FLAG_FADE_OUT = 1 << 5,
    FLAG_VOLUME_ANM = 1 << 6,
    FLAG_PAN_ANM = 1 << 7,
    FLAG_PAN = 1 << 8,
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
  bool isPlay() const { return (unknown08 & FLAG_PLAY) != 0; }
  bool isEnd() const { return (unknown08 & FLAG_END) != 0; }

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
