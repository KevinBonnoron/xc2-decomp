#pragma once
#include <stddef.h>

#include "rcha/rcha_node.h"
#include "types.h"

namespace mm {
struct Col4;
struct Vec3;
} // namespace mm

class RchaEff : public RchaNode {
public:
  static const int NAME_COUNT = 20; // Range marker, kept: the enum below has 20 enumerators, 0 to 19, and the array it sizes is indexed by them.

  // Slots of unknown19a4, in the order of the names (eff/ and effAtr/ tracks) that setup looks for.
  enum {
    EFF_UNKNOWN_0 = 0,      // Inferred role: eff translate x; original name unknown.
    EFF_UNKNOWN_1 = 1,      // Inferred role: eff translate y; original name unknown.
    EFF_UNKNOWN_2 = 2,      // Inferred role: eff translate z; original name unknown.
    EFF_UNKNOWN_3 = 3,      // Inferred role: eff rotate x; original name unknown.
    EFF_UNKNOWN_4 = 4,      // Inferred role: eff rotate y; original name unknown.
    EFF_UNKNOWN_5 = 5,      // Inferred role: eff rotate z; original name unknown.
    EFF_UNKNOWN_6 = 6,      // Inferred role: eff scale x; original name unknown.
    EFF_UNKNOWN_7 = 7,      // Inferred role: eff scale y; original name unknown.
    EFF_UNKNOWN_8 = 8,      // Inferred role: eff scale z; original name unknown.
    EFFATR_UNKNOWN_9 = 9,   // Inferred role: effatr translate x; original name unknown.
    EFFATR_UNKNOWN_10 = 10, // Inferred role: effatr translate y; original name unknown.
    EFFATR_UNKNOWN_11 = 11, // Inferred role: effatr translate z; original name unknown.
    EFFATR_UNKNOWN_12 = 12, // Inferred role: effatr rotate x; original name unknown.
    EFFATR_UNKNOWN_13 = 13, // Inferred role: effatr rotate y; original name unknown.
    EFFATR_UNKNOWN_14 = 14, // Inferred role: effatr rotate z; original name unknown.
    EFFATR_UNKNOWN_15 = 15, // Inferred role: effatr scale x; original name unknown.
    EFFATR_UNKNOWN_16 = 16, // Inferred role: effatr scale y; original name unknown.
    EFFATR_UNKNOWN_17 = 17, // Inferred role: effatr scale z; original name unknown.
    EFFATR_UNKNOWN_18 = 18, // Inferred role: effatr end; original name unknown.
    EFFATR_UNKNOWN_19 = 19, // Inferred role: effatr kill; original name unknown.
  };

  RchaEff();
  virtual void clear();
  virtual bool setup(mtl::ALLOC_HANDLE handle, const void *data);
  static bool hasAnm(const void *data);
  f32 getValue(int slot, f32 frame, f32 defaultValue) const;
  int getValueInt(int slot, f32 frame, int defaultValue) const;
  bool getPos(mm::Vec3 &pos, f32 frame) const;
  bool getRot(mm::Vec3 &rot, f32 frame) const;
  bool getScl(mm::Vec3 &scale, f32 frame) const;
  bool getProgress(int &current, int &total, f32 frame) const;
  bool getCol(mm::Col4 &color, f32 frame) const;
  bool isGenelate(f32 frame) const;
  bool isEnd(f32 frame) const;
  bool isKill(f32 frame) const;
  bool getSpeed(f32 &speed, f32 frame) const;

private:
  bool unknown19a0;            // Inferred role: has any named track; original member name unknown.
  int unknown19a4[NAME_COUNT]; // Inferred role: track index of each name; original member name unknown.

  friend struct RchaEffLayout;
};

struct RchaEffLayout {
  static_assert(offsetof(RchaEff, unknown19a0) == 0x19a0, "");
  static_assert(offsetof(RchaEff, unknown19a4) == 0x19a4, "");
  static_assert(sizeof(RchaEff) == 0x19f8, "");
};
