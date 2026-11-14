#pragma once
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace event {

class VolumeSkip {
public:
  static const f32 DEF_VOL;    // Name given by the xc2 symbol _ZN5event10VolumeSkip7DEF_VOLE.
  static const f32 DEF_IN_FR;  // Name given by the xc2 symbol _ZN5event10VolumeSkip9DEF_IN_FRE.
  static const f32 DEF_OUT_FR; // Name given by the xc2 symbol _ZN5event10VolumeSkip10DEF_OUT_FRE.

  enum TYPE {
    TYPE_UNKNOWN_0 = 0,   // Inferred role: bgm; original name unknown.
    TYPE_UNKNOWN_1 = 1,   // Inferred role: voi; original name unknown.
    TYPE_UNKNOWN_2 = 2,   // Inferred role: btl; original name unknown.
    TYPE_UNKNOWN_3 = 3,   // Inferred role: fld; original name unknown.
    TYPE_UNKNOWN_4 = 4,   // Inferred role: gmk; original name unknown.
    TYPE_UNKNOWN_5 = 5,   // Inferred role: env; original name unknown.
    TYPE_UNKNOWN_6 = 6,   // Inferred role: wea; original name unknown.
    TYPE_UNKNOWN_7 = 7,   // Inferred role: evtcs; original name unknown.
    TYPE_UNKNOWN_8 = 8,   // Inferred role: evtvoi; original name unknown.
    TYPE_UNKNOWN_9 = 9,   // Inferred role: evtse; original name unknown.
    TYPE_UNKNOWN_10 = 10, // Inferred role: chrse; original name unknown.
    TYPE_UNKNOWN_11 = 11, // Inferred role: noslow; original name unknown.
    TYPE_UNKNOWN_12 = 12, // Inferred role: enevoi; original name unknown.
    TYPE_UNKNOWN_13 = 13, // Inferred role: narevoi; original name unknown.
    TYPE_UNKNOWN_14 = 14, // Inferred role: count; original name unknown.
  };

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: enable flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: start flag; original name unknown.
  };

  VolumeSkip();
  virtual ~VolumeSkip() {}
  void clear();
  void set(bool isEnable, f32 volume, f32 inFrame, f32 outFrame, const mm::mtl::FixedArray<f32, TYPE_UNKNOWN_14> *resetVolumes);
  void start();
  void end();
  void setResetVolume(TYPE type, f32 volume);
  bool isStart() const { return (unknown08 & FLAG_UNKNOWN_1) != 0; }

private:
  u32 unknown08;                                       // Inferred role: flags; original member name unknown.
  mm::mtl::FixedArray<f32, TYPE_UNKNOWN_14> unknown0c; // Inferred role: reset volumes; original member name unknown.
  f32 unknown44;                                       // Inferred role: volume; original member name unknown.
  f32 unknown48;                                       // Inferred role: in frame; original member name unknown.
  f32 unknown4c;                                       // Inferred role: out frame; original member name unknown.
};

static_assert(sizeof(VolumeSkip) == 0x50, "");

} // namespace event
