#pragma once
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace event {

class VolumeSeamless {
public:
  static const f32 DEF_VOL;                          // Name given by the xc2 symbol _ZN5event14VolumeSeamless7DEF_VOLE.
  static constexpr u32 RESET_VOLUME_UNKNOWN_13 = 13; // Inferred role: reset volume count; original name unknown.

  enum TGT_TYPE {
    TGT_TYPE_UNKNOWN_0 = 1 << 0,   // Inferred role: bgm; original name unknown.
    TGT_TYPE_UNKNOWN_1 = 1 << 1,   // Inferred role: voi; original name unknown.
    TGT_TYPE_UNKNOWN_3 = 1 << 3,   // Inferred role: btl; original name unknown.
    TGT_TYPE_UNKNOWN_4 = 1 << 4,   // Inferred role: fld; original name unknown.
    TGT_TYPE_UNKNOWN_5 = 1 << 5,   // Inferred role: gmk; original name unknown.
    TGT_TYPE_UNKNOWN_6 = 1 << 6,   // Inferred role: env; original name unknown.
    TGT_TYPE_UNKNOWN_7 = 1 << 7,   // Inferred role: wea; original name unknown.
    TGT_TYPE_UNKNOWN_9 = 1 << 9,   // Inferred role: evtvoi (label "EVTVOI" of VolumeSeamless::draw); original name unknown.
    TGT_TYPE_UNKNOWN_10 = 1 << 10, // Inferred role: evtse (label "EVTSE" of VolumeSeamless::draw); original name unknown.
    TGT_TYPE_UNKNOWN_11 = 1 << 11, // Inferred role: chrse (label "CHRSE" of VolumeSeamless::draw); original name unknown.
    TGT_TYPE_UNKNOWN_12 = 1 << 12, // Inferred role: noslow (label "(NOSLOW)" of VolumeSeamless::draw); original name unknown.
    TGT_TYPE_UNKNOWN_13 = 1 << 13, // Inferred role: enevoi (label "ENEVOI" of VolumeSeamless::draw); original name unknown.
    TGT_TYPE_UNKNOWN_14 = 1 << 14, // Inferred role: narevoi (label "NAREVOI" of VolumeSeamless::draw); original name unknown.
  };

  enum MASK_TYPE {
    MASK_TYPE_UNKNOWN_0 = TGT_TYPE_UNKNOWN_0,   // Inferred role: bgm; original name unknown.
    MASK_TYPE_UNKNOWN_1 = TGT_TYPE_UNKNOWN_1,   // Inferred role: voi; original name unknown.
    MASK_TYPE_UNKNOWN_3 = TGT_TYPE_UNKNOWN_3,   // Inferred role: btl; original name unknown.
    MASK_TYPE_UNKNOWN_4 = TGT_TYPE_UNKNOWN_4,   // Inferred role: fld; original name unknown.
    MASK_TYPE_UNKNOWN_5 = TGT_TYPE_UNKNOWN_5,   // Inferred role: gmk; original name unknown.
    MASK_TYPE_UNKNOWN_6 = TGT_TYPE_UNKNOWN_6,   // Inferred role: env; original name unknown.
    MASK_TYPE_UNKNOWN_7 = TGT_TYPE_UNKNOWN_7,   // Inferred role: wea; original name unknown.
    MASK_TYPE_UNKNOWN_9 = TGT_TYPE_UNKNOWN_9,   // Inferred role: evtvoi (label "EVTVOI" of VolumeSeamless::draw); original name unknown.
    MASK_TYPE_UNKNOWN_10 = TGT_TYPE_UNKNOWN_10, // Inferred role: evtse (label "EVTSE" of VolumeSeamless::draw); original name unknown.
    MASK_TYPE_UNKNOWN_11 = TGT_TYPE_UNKNOWN_11, // Inferred role: chrse (label "CHRSE" of VolumeSeamless::draw); original name unknown.
    MASK_TYPE_UNKNOWN_12 = TGT_TYPE_UNKNOWN_12, // Inferred role: noslow (label "(NOSLOW)" of VolumeSeamless::draw); original name unknown.
    MASK_TYPE_UNKNOWN_13 = TGT_TYPE_UNKNOWN_13, // Inferred role: enevoi (label "ENEVOI" of VolumeSeamless::draw); original name unknown.
    MASK_TYPE_UNKNOWN_14 = TGT_TYPE_UNKNOWN_14, // Inferred role: narevoi (label "NAREVOI" of VolumeSeamless::draw); original name unknown.
  };

  enum {
    FLAG_UNKNOWN_0 = 0, // Inferred role: enable flag; original name unknown.
    FLAG_UNKNOWN_1 = 1, // Inferred role: start flag; original name unknown.
    FLAG_UNKNOWN_2 = 2, // Inferred role: end flag; original name unknown.
  };

  VolumeSeamless();
  virtual ~VolumeSeamless() {}
  void clear();
  void update();
  void draw();
  void set(bool isEnable, f32 volume, u32 target, const mm::mtl::FixedArray<f32, RESET_VOLUME_UNKNOWN_13> *resetVolumes);
  void start(f32 frame);
  void end(f32 frame);
  void setTarget(TGT_TYPE target);
  void mask(MASK_TYPE type, bool isMask);

private:
  bool isActive(u32 target) const { return (m_target & target) != 0 && (unknown10 & target) == 0; }

  mm::mtl::unknown027<32> unknown08; // Inferred role: flags; original member name unknown.
  u32 m_target;
  u32 unknown10;                                               // Inferred role: mask; original member name unknown.
  mm::mtl::FixedArray<f32, RESET_VOLUME_UNKNOWN_13> unknown14; // Inferred role: reset volumes; original member name unknown.
  f32 unknown48;                                               // Inferred role: volume; original member name unknown.
  f32 unknown4c;                                               // Inferred role: frame; original member name unknown.
};

static_assert(sizeof(VolumeSeamless) == 0x50, "");

} // namespace event
