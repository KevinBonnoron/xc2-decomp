#pragma once
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace event {

class VolumeSkip {
public:
  static const f32 DEF_VOL;
  static const f32 DEF_IN_FR;
  static const f32 DEF_OUT_FR;

  enum TYPE {
    TYPE_COUNT = 14,
  };

  enum {
    FLAG_ENABLE = 1 << 0,
    FLAG_START = 1 << 1,
  };

  VolumeSkip();
  virtual ~VolumeSkip() {}
  void clear();
  void set(bool isEnable, f32 volume, f32 inFrame, f32 outFrame, const mm::mtl::FixedArray<f32, TYPE_COUNT> *resetVolumes);
  void start();
  void end();
  void setResetVolume(TYPE type, f32 volume);
  bool isStart() const { return (unknown08 & FLAG_START) != 0; }

private:
  u32 unknown08;                                  // Inferred role: flags; original member name unknown.
  mm::mtl::FixedArray<f32, TYPE_COUNT> unknown0c; // Inferred role: reset volumes; original member name unknown.
  f32 unknown44;                                  // Inferred role: volume; original member name unknown.
  f32 unknown48;                                  // Inferred role: in frame; original member name unknown.
  f32 unknown4c;                                  // Inferred role: out frame; original member name unknown.
};

static_assert(sizeof(VolumeSkip) == 0x50, "");

} // namespace event
