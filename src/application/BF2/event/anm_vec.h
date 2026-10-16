#pragma once
#include "event/anm_base.h"
#include "event/curve.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include <stddef.h>

namespace event {

class AnmVec : public AnmBase {
public:
  AnmVec();
  virtual ~AnmVec() {}
  void clear();
  void update(f32 delta);
  mm::Vec3 calcEvalute(size_t index, f32 alpha) const;
  void replay();
  void append(f32 frame, const mm::Vec3 &value, CV_TYPE cv);
  void insert(size_t index, const mm::Vec3 &value);
  size_t count() const;
  CV_TYPE getCv(size_t index) const;
  const mm::Vec3 &getValue(size_t index) const;
  void setValue(size_t index, const mm::Vec3 &value);

private:
  mm::mtl::FixedVector<mm::Vec3, KEY_COUNT> values;
  mm::mtl::FixedVector<CV_TYPE, KEY_COUNT> cvs;
  mm::Vec3 value;
};

static_assert(sizeof(AnmVec) == 0x1f0, "");

} // namespace event
