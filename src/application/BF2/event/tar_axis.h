#pragma once
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

class TarAxis {
public:
  TarAxis();
  TarAxis(u32 axis, f32 x, f32 y, f32 z);
  TarAxis(u32 axis, const mm::Vec3 &tar);
  virtual ~TarAxis() {}
  void set(u32 axis, f32 x, f32 y, f32 z);
  void set(u32 axis, const mm::Vec3 &tar);
  mm::Vec3 calcTar(const mm::Vec3 &pos) const;
  mm::Mat44 calcOrigMat() const;
  const char *getOrigName() const;

private:
  u32 mAxis;
  mm::Vec3 mTar;
};

static_assert(sizeof(TarAxis) == 0x20, "");

} // namespace event
