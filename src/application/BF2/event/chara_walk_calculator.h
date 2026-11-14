#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

class CharaWalkCalculator {
public:
  static constexpr u32 LENGTH_UNKNOWN_50 = 50; // Inferred role: length count; original name unknown.

  enum TYPE {
    TYPE_UNKNOWN_0 = 0, // Inferred role: none; original name unknown.
    TYPE_UNKNOWN_1 = 1, // Inferred role: walk; original name unknown.
    TYPE_UNKNOWN_2 = 2, // Inferred role: walk start; original name unknown.
    TYPE_UNKNOWN_3 = 3, // Inferred role: walk stop; original name unknown.
    TYPE_UNKNOWN_4 = 4, // Inferred role: run; original name unknown.
    TYPE_UNKNOWN_5 = 5, // Inferred role: run start; original name unknown.
    TYPE_UNKNOWN_6 = 6, // Inferred role: run stop; original name unknown.
  };

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: active flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: run flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: acc flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: dec flag; original name unknown.
  };

  static bool s_initializeAcc;
  static bool s_initializeDec;
  static f32 s_lengthAcc[2][LENGTH_UNKNOWN_50];
  static f32 s_lengthDec[2][LENGTH_UNKNOWN_50];

  CharaWalkCalculator();
  void clear();
  void setup(TYPE type, const mm::Vec3 &from, const mm::Vec3 &to);
  static f32 getBlend(bool isRun);
  f32 calcTotalFrame(f32 length) const;
  void update(f32 delta);
  mm::Vec3 calcPos(f32 frame) const;
  f32 calcSpeed(f32 frame) const;
  static f32 getAccLength(bool isRun, f32 frame);
  static f32 getTopSpeed(bool isRun);
  static f32 getDecLength(bool isRun, f32 frame);
  static f32 getAccSpeed(bool isRun, f32 frame);
  static f32 getDecSpeed(bool isRun, f32 frame);
  static void test();

private:
  u32 unknown00;      // Inferred role: flags; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: from; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: to; original member name unknown.
  f32 unknown30;      // Inferred role: distance; original member name unknown.
  mm::Vec3 unknown40; // Inferred role: dir; original member name unknown.
  mm::Vec3 unknown50; // Inferred role: dir xz; original member name unknown.
  f32 unknown60;      // Inferred role: blend; original member name unknown.
  f32 unknown64;      // Inferred role: total frame; original member name unknown.
  mm::Vec3 unknown70; // Inferred role: pos; original member name unknown.
  f32 unknown80;      // Inferred role: speed; original member name unknown.
  f32 unknown84;      // Inferred role: frame; original member name unknown.
};

static_assert(sizeof(CharaWalkCalculator) == 0x90, "");

} // namespace event
