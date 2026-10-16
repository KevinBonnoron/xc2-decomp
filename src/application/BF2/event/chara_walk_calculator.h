#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

class CharaWalkCalculator {
public:
  static constexpr u32 LENGTH_COUNT = 50;

  enum TYPE {
    TYPE_NONE = 0,
    TYPE_WALK = 1,
    TYPE_WALK_START = 2,
    TYPE_WALK_STOP = 3,
    TYPE_RUN = 4,
    TYPE_RUN_START = 5,
    TYPE_RUN_STOP = 6,
  };

  enum {
    FLAG_ACTIVE = 1 << 0,
    FLAG_RUN = 1 << 1,
    FLAG_ACC = 1 << 2,
    FLAG_DEC = 1 << 3,
  };

  static bool s_initializeAcc;
  static bool s_initializeDec;
  static f32 s_lengthAcc[2][LENGTH_COUNT];
  static f32 s_lengthDec[2][LENGTH_COUNT];

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
  u32 flags;
  mm::Vec3 mFrom;
  mm::Vec3 mTo;
  f32 mDistance;
  mm::Vec3 mDir;
  mm::Vec3 mDirXZ;
  f32 mBlend;
  f32 mTotalFrame;
  mm::Vec3 mPos;
  f32 mSpeed;
  f32 frame;
};

static_assert(sizeof(CharaWalkCalculator) == 0x90, "");

} // namespace event
