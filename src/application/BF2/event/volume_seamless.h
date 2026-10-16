#pragma once
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace event {

class VolumeSeamless {
public:
  static const f32 DEF_VOL;
  static constexpr u32 RESET_VOLUME_COUNT = 13;

  enum TGT_TYPE {
    TGT_TYPE_BGM = 1 << 0,
    TGT_TYPE_VOI = 1 << 1,
    TGT_TYPE_BTL = 1 << 3,
    TGT_TYPE_FLD = 1 << 4,
    TGT_TYPE_GMK = 1 << 5,
    TGT_TYPE_ENV = 1 << 6,
    TGT_TYPE_WEA = 1 << 7,
    TGT_TYPE_EVTVOI = 1 << 9,
    TGT_TYPE_EVTSE = 1 << 10,
    TGT_TYPE_CHRSE = 1 << 11,
    TGT_TYPE_NOSLOW = 1 << 12,
    TGT_TYPE_ENEVOI = 1 << 13,
    TGT_TYPE_NAREVOI = 1 << 14,
  };

  enum MASK_TYPE {
    MASK_TYPE_BGM = TGT_TYPE_BGM,
    MASK_TYPE_VOI = TGT_TYPE_VOI,
    MASK_TYPE_BTL = TGT_TYPE_BTL,
    MASK_TYPE_FLD = TGT_TYPE_FLD,
    MASK_TYPE_GMK = TGT_TYPE_GMK,
    MASK_TYPE_ENV = TGT_TYPE_ENV,
    MASK_TYPE_WEA = TGT_TYPE_WEA,
    MASK_TYPE_EVTVOI = TGT_TYPE_EVTVOI,
    MASK_TYPE_EVTSE = TGT_TYPE_EVTSE,
    MASK_TYPE_CHRSE = TGT_TYPE_CHRSE,
    MASK_TYPE_NOSLOW = TGT_TYPE_NOSLOW,
    MASK_TYPE_ENEVOI = TGT_TYPE_ENEVOI,
    MASK_TYPE_NAREVOI = TGT_TYPE_NAREVOI,
  };

  enum {
    FLAG_ENABLE = 0,
    FLAG_START = 1,
    FLAG_END = 2,
  };

  VolumeSeamless();
  virtual ~VolumeSeamless() {}
  void clear();
  void update();
  void draw();
  void set(bool isEnable, f32 volume, u32 target, const mm::mtl::FixedArray<f32, RESET_VOLUME_COUNT> *resetVolumes);
  void start(f32 frame);
  void end(f32 frame);
  void setTarget(TGT_TYPE target);
  void mask(MASK_TYPE type, bool isMask);

private:
  bool isActive(u32 target) const { return (mTarget & target) != 0 && (mMask & target) == 0; }

  mm::mtl::BitFlag<32> flags;
  u32 mTarget;
  u32 mMask;
  mm::mtl::FixedArray<f32, RESET_VOLUME_COUNT> mResetVolumes;
  f32 mVolume;
  f32 frame;
};

static_assert(sizeof(VolumeSeamless) == 0x50, "");

} // namespace event
