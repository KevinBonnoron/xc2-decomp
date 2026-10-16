#pragma once
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

class TarAxis {
public:
  enum {
    AXIS_NONE = 0,
    AXIS_POS = 1,
    AXIS_POS_GLOBAL = 2,
    AXIS_SAY = 3,
    AXIS_ANGLE = 4,
    AXIS_ANGLE_GLOBAL = 5,
    AXIS_CHARA = 6,
  };

  TarAxis();
  TarAxis(u32 axis, f32 x, f32 y, f32 z);
  TarAxis(u32 axis, const mm::Vec3 &tar);
  virtual ~TarAxis() {}
  void set(u32 axis, f32 x, f32 y, f32 z);
  void set(u32 axis, const mm::Vec3 &tar);
  mm::Vec3 calcTar(const mm::Vec3 &pos) const;
  mm::Mat44 calcOrigMat() const;
  const char *getOrigName() const;
  u32 getAxis() const { return mAxis; }
  const mm::Vec3 &getTar() const { return mTar; }

private:
  u32 mAxis;
  mm::Vec3 mTar;
};

static_assert(sizeof(TarAxis) == 0x20, "");

} // namespace event
