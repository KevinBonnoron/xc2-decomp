#pragma once
#include <stddef.h>

#include "rcha/rcha_anm.h"
#include "rcha/rcha_node.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

class RchaChrEff : public RchaNode {
public:
  static const int NAME_COUNT = 20; // Range marker, kept: the enum below has 20 enumerators, 0 to 19, and the array it sizes is indexed by them.

  // Slots of unknown19a4, in the order of the names (chrEff/ tracks) that setup looks for.
  enum {
    CHREFF_UNKNOWN_0 = 0,   // Inferred role: chreff volume fade; original name unknown.
    CHREFF_UNKNOWN_1 = 1,   // Inferred role: chreff volume fade id; original name unknown.
    CHREFF_UNKNOWN_2 = 2,   // Inferred role: chreff volume fade uvw scale x; original name unknown.
    CHREFF_UNKNOWN_3 = 3,   // Inferred role: chreff volume fade uvw scale y; original name unknown.
    CHREFF_UNKNOWN_4 = 4,   // Inferred role: chreff volume fade uvw scale z; original name unknown.
    CHREFF_UNKNOWN_5 = 5,   // Inferred role: chreff volume fade center pos x; original name unknown.
    CHREFF_UNKNOWN_6 = 6,   // Inferred role: chreff volume fade center pos y; original name unknown.
    CHREFF_UNKNOWN_7 = 7,   // Inferred role: chreff volume fade center pos z; original name unknown.
    CHREFF_UNKNOWN_8 = 8,   // Inferred role: chreff volume fade distance; original name unknown.
    CHREFF_UNKNOWN_9 = 9,   // Inferred role: chreff volume fade directivity; original name unknown.
    CHREFF_UNKNOWN_10 = 10, // Inferred role: chreff volume fade mesh no; original name unknown.
    CHREFF_UNKNOWN_11 = 11, // Inferred role: chreff volume fade ratio; original name unknown.
    CHREFF_UNKNOWN_12 = 12, // Inferred role: chreff rim bloom; original name unknown.
    CHREFF_UNKNOWN_13 = 13, // Inferred role: chreff rim bloom id; original name unknown.
    CHREFF_UNKNOWN_14 = 14, // Inferred role: chreff after image; original name unknown.
    CHREFF_UNKNOWN_15 = 15, // Inferred role: chreff after image id1; original name unknown.
    CHREFF_UNKNOWN_16 = 16, // Inferred role: chreff after image id2; original name unknown.
    CHREFF_UNKNOWN_17 = 17, // Inferred role: chreff after image capture frame; original name unknown.
    CHREFF_UNKNOWN_18 = 18, // Inferred role: chreff after image exist frame; original name unknown.
    CHREFF_UNKNOWN_19 = 19, // Inferred role: chreff after image fade out frame; original name unknown.
  };

  RchaChrEff();
  virtual void clear();
  virtual bool setup(mtl::ALLOC_HANDLE handle, const void *data);
  static bool hasAnm(const void *data);
  f32 getValue(int slot, f32 frame, f32 defaultValue) const;
  int getValueInt(int slot, f32 frame, int defaultValue) const;
  bool getVolumeFade(int &type, f32 frame) const;
  bool getVolumeFadeId(int &id, f32 frame) const;
  void getVolumeFadeUVWScale(mm::Vec3 &scale, f32 frame) const;
  void getVolumeFadeCenterPos(mm::Vec3 &pos, f32 frame) const;
  bool getVolumeFadeDistance(f32 &distance, f32 frame) const;
  bool getVolumeFadeDirectivity(f32 &directivity, f32 frame) const;
  bool getVolumeFadeMesh(int &mesh, f32 frame) const;
  bool getVolumeFadeRatio(f32 &ratio, f32 frame) const;
  bool getRimBloom(int &type, f32 frame) const;
  bool getRimBloomId(int &id, f32 frame) const;
  bool getAfterImage(int &type, f32 frame) const;
  bool getAfterImageId1(int &id, f32 frame) const;
  bool getAfterImageId2(int &id, f32 frame) const;
  bool getAfterImageCaptureFrame(f32 &captureFrame, f32 frame) const;
  bool getAfterImageExistFrame(f32 &existFrame, f32 frame) const;
  bool getAfterImageFadeOutFrame(f32 &fadeOutFrame, f32 frame) const;

private:
  // Inferred helpers: read the track of a slot as an int or a float when the resource has it; original names unknown.
  bool unknown001(int &value, int slot, f32 frame) const {
    int index = unknown19a4[slot];
    if (index >= 0) {
      value = unknown10[index].getValueInt(frame);
      return true;
    }
    return false;
  }

  bool unknown002(f32 &value, int slot, f32 frame) const {
    int index = unknown19a4[slot];
    if (index >= 0) {
      value = unknown10[index].getValue(frame);
      return true;
    }
    return false;
  }

  bool unknown19a0;            // Inferred role: has any named track; original member name unknown.
  int unknown19a4[NAME_COUNT]; // Inferred role: track index of each name; original member name unknown.

  friend struct RchaChrEffLayout;
};

struct RchaChrEffLayout {
  static_assert(offsetof(RchaChrEff, unknown19a0) == 0x19a0, "");
  static_assert(offsetof(RchaChrEff, unknown19a4) == 0x19a4, "");
  static_assert(sizeof(RchaChrEff) == 0x19f8, "");
};
